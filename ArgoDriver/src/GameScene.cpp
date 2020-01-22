#include "GameScene.h"

std::map<GLchar, Character> GameScene::Characters;

GameScene::GameScene(SDL_Window* window) : Scene("Game")
{
	m_levelManager = LevelManager();
	m_enemy = new Entity();
	m_civOne = new Entity();
	m_civTwo = new Entity();
	m_cam = new Camera(m_levelManager.GetCameraStartPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
	m_window = window;

	m_sky.init();

	m_textShader = ResourceManager::getInstance()->GetShader("text");
	m_lightingShader = ResourceManager::getInstance()->GetShader("model");	
	
	srand(time(NULL));

	int track;

	track = rand() % 3;

	if (track == 1)
	{
		m_bgmGame = SoundEngine->play2D("Assets\\audio\\music5.wav", GL_TRUE, GL_TRUE);
	}
	else if (track == 2)
	{
		m_bgmGame = SoundEngine->play2D("Assets\\audio\\music2.wav", GL_TRUE, GL_TRUE);
	}
	else
	{
		m_bgmGame = SoundEngine->play2D("Assets\\audio\\bgm.mp3", GL_TRUE, GL_TRUE);
	}

	/*m_bgmGame->setVolume(0.3);
	m_engineEffect = SoundEngine->play2D("Assets\\audio\\loop1.wav", GL_TRUE, GL_TRUE);*/

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	PointLight p;
	for (int i = 0; i < m_levelManager.listOfRoadPositions.size(); i++)
	{
		p.position = glm::vec3(m_levelManager.listOfRoadPositions[i].x, m_levelManager.GetCameraStartPosition().y + 15, m_levelManager.listOfRoadPositions[i].z);
		p.ambient = glm::vec3((rand() % 50) / 100.f, (rand() % 50) / 100.f, (rand() % 50) / 100.f);
		p.diffuse = glm::vec3(p.ambient.x * 2, p.ambient.y * 2, p.ambient.z * 2);
		p.ambient *= glm::vec3(3,3,3);
		p.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		p.constant = 1.0f;
		p.linear = 0.014;
		p.quadratic = 0.0007;
		m_pointLights.push_back(p);
	}		

	m_directionalLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	m_directionalLight.ambient = glm::vec3(0.025f, 0.025f, 0.025f);
	m_directionalLight.diffuse = glm::vec3(0.1, 0.1, 0.1);
	m_directionalLight.specular	= glm::vec3(0.5f, 0.5f, 0.5f);

	m_lightingShader.Use();
	//Point lights
	for (int i = 0; i < m_pointLights.size(); i++)
	{
		std::string number = std::to_string(i);
		glUniform3f(glGetUniformLocation(m_lightingShader.ID, ("pointLights[" + number + "].position").c_str())	, m_pointLights[i].position.x, m_pointLights[i].position.y, m_pointLights[i].position.z);
		glUniform3f(glGetUniformLocation(m_lightingShader.ID, ("pointLights[" + number + "].ambient").c_str())	, m_pointLights[i].ambient.x, m_pointLights[i].ambient.y, m_pointLights[i].ambient.z);
		glUniform3f(glGetUniformLocation(m_lightingShader.ID, ("pointLights[" + number + "].diffuse").c_str())	, m_pointLights[i].diffuse.x, m_pointLights[i].diffuse.y, m_pointLights[i].diffuse.z);
		glUniform3f(glGetUniformLocation(m_lightingShader.ID, ("pointLights[" + number + "].specular").c_str())	, m_pointLights[i].specular.x, m_pointLights[i].specular.y, m_pointLights[i].specular.z);
		glUniform1f(glGetUniformLocation(m_lightingShader.ID, ("pointLights[" + number + "].constant").c_str())	, m_pointLights[i].constant);
		glUniform1f(glGetUniformLocation(m_lightingShader.ID, ("pointLights[" + number + "].linear").c_str())	, m_pointLights[i].linear);
		glUniform1f(glGetUniformLocation(m_lightingShader.ID, ("pointLights[" + number + "].quadratic").c_str()), m_pointLights[i].quadratic);
	}

	// Directional light
	glUniform3f(glGetUniformLocation(m_lightingShader.ID, "dirLight.direction"), m_directionalLight.direction.x, m_directionalLight.direction.y, m_directionalLight.direction.z);
	glUniform3f(glGetUniformLocation(m_lightingShader.ID, "dirLight.ambient"), m_directionalLight.ambient.x, m_directionalLight.ambient.y, m_directionalLight.ambient.z);
	glUniform3f(glGetUniformLocation(m_lightingShader.ID, "dirLight.diffuse"), m_directionalLight.diffuse.x, m_directionalLight.diffuse.y, m_directionalLight.diffuse.z);
	glUniform3f(glGetUniformLocation(m_lightingShader.ID, "dirLight.specular"), m_directionalLight.specular.x, m_directionalLight.specular.y, m_directionalLight.specular.z);

	m_textShader.Use();
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREENWIDTH), 0.0f, static_cast<GLfloat>(SCREENHEIGHT));
	glUniformMatrix4fv(glGetUniformLocation(m_textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	Characters = ResourceManager::getInstance()->setUpTextObjects();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

GameScene::~GameScene()
{
	for (int i = 0; i < m_players.size(); i++)
	{
		delete m_players[i];
		m_players[i] = nullptr;
	}

	delete m_checkPoint;
	m_checkPoint = nullptr;

	delete m_enemy;
	m_enemy = nullptr;

	delete m_civOne;
	m_civOne = nullptr;

	delete m_civTwo;
	m_civTwo = nullptr;
}

void GameScene::Pause()
{
	this->SetDead("Menu");
}

void GameScene::Exit()
{
	this->SetDead("CLOSE");
}

void GameScene::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	m_textShader.Use();

	glUniform3f(glGetUniformLocation(m_textShader.ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameScene::Start()
{
	if (m_net->IsConnected())
		m_playerCount = m_net->GetNoOfPlayers();
	else
		m_playerCount = 1;

	InitEntities();
	InitSystems();
}

void GameScene::Update(float dt)
{	
	//m_bgmGame->setIsPaused(false);
	if (m_net->IsConnected())
	{
		m_multiplayerSystem.Update(dt);
		if (m_net->GetMessage()[0] == "gameover")
			this->SetDead("GameOver");
	}
	if (m_checkpointSystem.GetLaps() == 3)
		this->SetDead("GameOver");
	ExitControls();
	m_levelManager.Update(dt);
	m_transformSystem.Update(dt);
	m_cameraSystem.Chase(dt);
	m_polygonBoundsSystem.Update(dt);
	m_mapCollisionSystem.Update(dt);
	m_AIMovementSystem.Update(dt);
	m_checkpointSystem.Update(dt);
	m_pickUpSystem.Update(dt);
	m_pickUpSystem.CheckForCollisions(m_players[0]);
}

void GameScene::Render()
{		
	scoreBoardY = 600;
	m_sky.render(m_cam, SCREENWIDTH, SCREENHEIGHT);
	m_lightingShader.Use();
	m_levelManager.Draw(m_cam, m_lightingShader);
	m_renderSystem.Draw(m_cam, m_lightingShader);
	m_polygonBoundsSystem.Draw(m_cam);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	RenderText("Lap Count: " + to_string(m_checkpointSystem.GetLaps()), 0, 0, 0.65f, glm::vec3(155, 0, 0));
	Velocity * v = (Velocity*)m_players[0]->GetComponent("velocity");
	RenderText("Speed: " + to_string(v->m_acceleration), 800, 0, 0.65f, glm::vec3(v->m_acceleration*31, 155 - (31 * v->m_acceleration), 0));
	RenderText("Handling: " + to_string(lapTimer), 800, 25, 0.65f, glm::vec3(155, 0, 0));
	if (scoreboard)
	{
		for (int i = 0; i < m_leaderboard.size(); i++)
		{
			RenderText(m_leaderboard[i].name + ":" + to_string(m_leaderboard[i].lapTime), SCREENWIDTH / 3, scoreBoardY, 0.75f, glm::vec3(255, 0, 0));
			scoreBoardY -= (i+1) * 50;
		}
	}
	glDisable(GL_BLEND);
	SDL_GL_SwapWindow(m_window);
}

void GameScene::ExitControls()
{
	if (m_controllerSystem.GetPaused() == true)
	{
		m_bgmGame->setIsPaused(true);
		m_controllerSystem.Pause();
		this->SetDead("Menu");
	}

	if (m_controllerSystem.GetExit() == true)
	{
		this->SetDead("CLOSE");
	}
}

void GameScene::HandleInput(float dt)
{	
	m_controllerSystem.HandleInput(dt);
}

void GameScene::InitEntities()
{
	vector<glm::vec2*> boundPoints;
	boundPoints.push_back(new glm::vec2(-5, 5));
	boundPoints.push_back(new glm::vec2(5, 5));
	boundPoints.push_back(new glm::vec2(5, -5));
	boundPoints.push_back(new glm::vec2(-5, -5));
	//enemy
	m_enemy = new Entity();
	m_enemy->AddComponent(new Transformable(m_levelManager.GetCameraStartPosition(), 0, 0, 0));
	Transformable* ent = (Transformable*)m_enemy->GetComponent("transformable");
	m_enemy->AddComponent(new ModelMesh("shuttleOne", ent->m_position + glm::vec3(0, 7, 20), glm::vec3(0.014f, 0.014f, 0.014f), 0));
	m_enemy->AddComponent(new Velocity(0.1f, 1.f, 5.f));
	m_enemy->AddComponent(new PolygonBounds(boundPoints, ent->m_position));
	m_enemy->AddComponent(new AISteering());
	m_enemy->AddComponent(new IDTag("enemy"));

	m_civOne = new Entity();
	glm::vec3 pos = m_levelManager.listOfCarPointsOther[m_levelManager.listOfCarPoints.size() - 1];
	m_civOne->AddComponent(new Transformable(pos, 0, 0, 0));
	Transformable* civt = (Transformable*)m_civOne->GetComponent("transformable");
	
	m_civOne->AddComponent(new ModelMesh("car", civt->m_position + glm::vec3(0, 8, 0), glm::vec3(0.1f, 0.1f, 0.1f), 180));
	m_civOne->AddComponent(new Velocity(0.1f, 1.f, 5.f));
	Velocity * v = (Velocity*)m_civOne->GetComponent("velocity");
	v->m_acceleration = 1.0f;
	m_civOne->AddComponent(new PolygonBounds(boundPoints, civt->m_position));
	m_civOne->AddComponent(new AISteering());
	m_civOne->AddComponent(new IDTag("civOne"));

	m_civTwo = new Entity();
	pos = m_levelManager.listOfCarPointsOther[m_levelManager.listOfCarPointsOther.size() - 1];
	m_civTwo->AddComponent(new Transformable(pos, 0, 0, 0));
	Transformable* civtwo = (Transformable*)m_civTwo->GetComponent("transformable");
	m_civTwo->AddComponent(new ModelMesh("car", civtwo->m_position + glm::vec3(0, 10, 0), glm::vec3(0.1, 0.1f, 0.1f), 180));
	m_civTwo->AddComponent(new Velocity(0.1f, 1.f, 5.f));
	Velocity * evv = (Velocity*)m_civTwo->GetComponent("velocity");
	evv->m_acceleration = 1.0f;
	m_civTwo->AddComponent(new PolygonBounds(boundPoints, civtwo->m_position));
	m_civTwo->AddComponent(new AISteering());
	m_civTwo->AddComponent(new IDTag("civTwo"));

	float offset = 0;
	for (int i = 0; i < m_playerCount; i++)
	{
		Entity* m_player;
		if (m_net->GetMessage().size() != 0 && m_players.size() == 0)
		{
			m_player = new Entity("Player" + m_net->GetMessage()[1]);
			offset += 15 * atoi(m_net->GetMessage()[1].c_str());
			m_player->id = atoi(m_net->GetMessage()[1].c_str());
			m_player->playerSet = true;
		}
		else if (m_net->GetMessage().size() != 0 && m_players.size() != 0)
		{
			m_player = new Entity("remotePlayer");
			m_player->playerSet = false;
		}
		else
		{
			m_player = new Entity("Player");
			offset = 15;
		}
		m_player->AddComponent(new Transformable(m_levelManager.GetCameraStartPosition(), 0, 0, 0));
		m_player->AddComponent(new Velocity(0.1f, 1.f, 5.f));

		Transformable* t = (Transformable*)m_player->GetComponent("transformable");
		m_player->AddComponent(new ModelMesh("shuttleOne", t->m_position, glm::vec3(0.02f, 0.02f, 0.02f), 0));

		vector<glm::vec2*> boundPoints;
		boundPoints.push_back(new glm::vec2(-2, 2));
		boundPoints.push_back(new glm::vec2(2, 2));
		boundPoints.push_back(new glm::vec2(2, -2));
		boundPoints.push_back(new glm::vec2(-2, -2));
		m_player->AddComponent(new PolygonBounds(boundPoints, t->m_position));
		m_players.push_back(m_player);
	}

	Transformable* t = (Transformable*)m_players[0]->GetComponent("transformable");
	vector<glm::vec2*> boundPointsC;
	m_checkPoint = new Entity("check");
	m_checkPoint->AddComponent(new Transformable(glm::vec3(m_levelManager.offsetX, 0, m_levelManager.offsetY), 0, 0, 0));
	Transformable* ct = (Transformable*)m_checkPoint->GetComponent("transformable");

	m_checkPoint->AddComponent(new ModelMesh("pickup", ct->m_position + glm::vec3(0, 10, 0), glm::vec3(0.10f, 0.10f, 0.10f), 0));

	boundPointsC.push_back(new glm::vec2(-8, 8));
	boundPointsC.push_back(new glm::vec2(8, 8));
	boundPointsC.push_back(new glm::vec2(8, -8));
	boundPointsC.push_back(new glm::vec2(-8, -8));
	m_checkPoint->AddComponent(new PolygonBounds(boundPointsC, ct->m_position));

	m_pickUp = new Entity();
	m_pickUp = m_pickUpSystem.CreateMine(m_players[0]);
}

void GameScene::InitSystems()
{
	m_renderSystem = RenderSystem();
	m_controllerSystem = ControllerSystem();
	m_transformSystem = TransformSystem();
	m_cameraSystem = CameraSystem(m_cam, m_players[0]);
	m_polygonBoundsSystem = PolygonBoundsSystem();
	m_checkpointSystem = CheckpointSystem();
	m_mapCollisionSystem = MapCollisionSystem();
	m_AIMovementSystem = AIMovementSystem(m_levelManager.listOfCheckpoints, m_levelManager.listOfCarPoints, m_levelManager.listOfCarPointsOther);

	m_AIMovementSystem.AddEntity(m_enemy);
	m_renderSystem.AddEntity(m_enemy);
	//m_transformSystem.AddEntity(m_enemy);
	m_mapCollisionSystem.AddObsticle(m_enemy);
	m_mapCollisionSystem.AddEntity(m_enemy);
	m_polygonBoundsSystem.AddEntity(m_enemy);

	m_AIMovementSystem.AddEntity(m_civOne);
	m_renderSystem.AddEntity(m_civOne);
	//m_transformSystem.AddEntity(m_civOne);
	m_mapCollisionSystem.AddObsticle(m_civOne);
	m_mapCollisionSystem.AddEntity(m_civOne);
	m_polygonBoundsSystem.AddEntity(m_civOne);

	m_AIMovementSystem.AddEntity(m_civTwo);
	m_renderSystem.AddEntity(m_civTwo);
	//m_transformSystem.AddEntity(m_civTwo);
	m_mapCollisionSystem.AddObsticle(m_civTwo);
	m_mapCollisionSystem.AddEntity(m_civTwo);
	m_polygonBoundsSystem.AddEntity(m_civTwo);

	if (m_net->IsConnected())
		m_multiplayerSystem = MultiplayerSystem(m_players);
	m_controllerSystem.SetEntity(m_players[0]);
	
	for (int i = 0; i < m_players.size(); i++)
	{
		m_renderSystem.AddEntity(m_players[i]);
		m_polygonBoundsSystem.AddEntity(m_players[i]);
		m_mapCollisionSystem.AddEntity(m_players[i]);
		m_AIMovementSystem.AddObjectToAvoid(m_players[i]);
	}

	m_transformSystem.AddEntity(m_players[0]);
	m_checkpointSystem.AddEntity(m_players[0]);
	m_checkpointSystem.AddCheckpoint(m_checkPoint);
	m_renderSystem.AddEntity(m_checkPoint);
	m_transformSystem.AddEntity(m_checkPoint);
	m_polygonBoundsSystem.AddEntity(m_checkPoint);

	m_pickUpSystem.AddEntity(m_pickUp);
	m_renderSystem.AddEntity(m_pickUp);
}

bool SortLapTimes(LapData ld1, LapData ld2)
{
	return ld1.lapTime < ld2.lapTime;
}
