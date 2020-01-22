#include "Game.h"

using namespace std;

Game::Game() : m_running(false)
{

}

Game::~Game()
{

}

bool Game::Initialize()
{
#pragma region InitialiseWindow

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_Window = SDL_CreateWindow("Argo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
		//SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
		if (m_Window != 0)
		{
			m_context = SDL_GL_CreateContext(m_Window);
			SetOpenGLAttributes();
			SDL_GL_SetSwapInterval(1);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	glewExperimental = GL_TRUE;
	glewInit();
#pragma endregion
#pragma region SetupScenes

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	m_sceneManager = new SceneManager();

	LoadResources();

	m_sceneManager->AddScene(new MenuScene(m_Renderer));
	m_sceneManager->AddScene(new OptionsScene(m_Renderer));
	m_sceneManager->AddScene(new GameScene(m_Window));
	m_sceneManager->AddScene(new MultiplayerScene(m_Renderer));
	m_sceneManager->AddScene(new GameOverScene(m_Renderer));
	m_sceneManager->SwitchScene("Menu");
#pragma endregion

	m_running = true;
	return true;
}

void Game::LoadResources()
{
	ResourceManager::getInstance()->SetUp(m_Renderer);
	//Load Shaders

	ResourceManager::getInstance()->LoadShader("Shaders\\skyBoxShader.vs", "Shaders\\skyBoxShader.frag", nullptr, "skybox");
	ResourceManager::getInstance()->LoadShader("Shaders\\texture.vs", "Shaders\\texture.frag", nullptr, "texture");
	ResourceManager::getInstance()->LoadShader("Shaders\\textureSun.vs", "Shaders\\textureSun.frag", nullptr, "cube");
	ResourceManager::getInstance()->LoadShader("Shaders\\basic.vs", "Shaders\\basic.frag", nullptr, "basic");
	ResourceManager::getInstance()->LoadShader("Shaders\\texture.vs", "Shaders\\texture.frag", nullptr, "ground");
	ResourceManager::getInstance()->LoadShader("Shaders\\lightShader.vs", "Shaders\\lightShader.frag", nullptr, "model");
	ResourceManager::getInstance()->LoadShader("Shaders\\textShader.vs", "Shaders\\textShader.frag", nullptr, "text");

	//Load Models
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\pickupPoint.obj", "pickup");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\streetLight.obj", "streetLight");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\barracks.obj", "barracks");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\car.obj", "car");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\dock.obj", "dock");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\landing.obj", "landing");//SciFiBuilding
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\SciFiBuilding.obj", "SciFiBuilding");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\vehicle_with_texture.obj", "shuttleOne");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\tall.obj", "tall");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\straight.obj", "straight");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\corner.obj", "corner");
	ResourceManager::getInstance()->LoadModel("Assets\\Models\\mine.obj", "mine");

	//Load Images
	//MAIN MENU
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\SpaceBackground1.bmp", "MenuBackground", glm::vec2(0, 0));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "PlayButton", glm::vec2(375, 150));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "MPButton", glm::vec2(375, 300));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "OptButton", glm::vec2(375, 450));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "QuitButton", glm::vec2(375, 600));
	ResourceManager::getInstance()->LoadText("argo driver", "MenuTitle", 40, glm::vec2(425, 50));
	ResourceManager::getInstance()->LoadText("play", "PlayText", 40, glm::vec2(450, 175));
	ResourceManager::getInstance()->LoadText("multiplayer", "MPText", 35, glm::vec2(400, 325));
	ResourceManager::getInstance()->LoadText("options", "OptionsText", 40, glm::vec2(425, 475));
	ResourceManager::getInstance()->LoadText("quit", "QuitText", 40, glm::vec2(450, 625));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\selectedButton.bmp", "highlight", glm::vec3(0, 0, 0));

	//MULTIPLAYER
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "ConnectButtonMP", glm::vec2(400, 200));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "MenuButtonMP", glm::vec2(400, 400));
	ResourceManager::getInstance()->LoadText("connect", "connectTextMP", 40, glm::vec2(425, 225));
	ResourceManager::getInstance()->LoadText("join game", "JoinTextMP", 40, glm::vec2(425, 425));

	//OPTIONS
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\return.bmp", "ReturnButton", glm::vec2(0, 650));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "AudioOptButton", glm::vec2(50, 150));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "GraphicsOptButton", glm::vec2(50, 300));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "GameOptButton", glm::vec2(50, 450));
	ResourceManager::getInstance()->LoadText("options", "OptionsTitle", 40, glm::vec2(475, 50));
	ResourceManager::getInstance()->LoadText("audio", "AudioOptText", 40, glm::vec2(75, 175));
	ResourceManager::getInstance()->LoadText("graphics", "GraphicsOptText", 40, glm::vec2(75, 325));
	ResourceManager::getInstance()->LoadText("game", "GameOptText", 40, glm::vec2(75, 475));

	//GAME OVER
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "ReturnButtonGO", glm::vec2(400, 300));
	ResourceManager::getInstance()->LoadTexture("Assets\\Images\\button.bmp", "QuitButtonGO", glm::vec2(400, 500));

	ResourceManager::getInstance()->LoadText("main menu", "ReturnTextGO", 40, glm::vec2(435, 325));
	ResourceManager::getInstance()->LoadText("quit", "QuitTextGO", 40, glm::vec2(475, 525));

	ResourceManager::getInstance()->LoadText("game over", "GameOverTitle", 40, glm::vec2(425, 50));
	ResourceManager::getInstance()->LoadText("you have lost", "GameOverText", 40, glm::vec2(380, 200));

	//load mesh textures for opengl
	ResourceManager::getInstance()->LoadTextureMesh("Assets\\Images\\container.png", "container");
	ResourceManager::getInstance()->LoadTextureMesh("Assets\\Images\\leftRight.jpg", "leftRight");
	ResourceManager::getInstance()->LoadTextureMesh("Assets\\Images\\upDown.jpg", "upDown");
	ResourceManager::getInstance()->LoadTextureMesh("Assets\\Images\\turndown.jpg", "turndown");
	ResourceManager::getInstance()->LoadTextureMesh("Assets\\Images\\opUp.jpg", "opUp");
	ResourceManager::getInstance()->LoadTextureMesh("Assets\\Images\\turnUp.jpg", "turnUp");
	ResourceManager::getInstance()->LoadTextureMesh("Assets\\Images\\opDown.jpg", "opDown");
}

bool Game::SetOpenGLAttributes() {

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return true;
}

void Game::SetupScenes()
{
	
}

void Game::Update(float dt) {

	if (m_sceneManager->GetCurrentScene()->CheckDead() == false)
	{
		if (m_sceneManager->GetCurrentScene()->CheckNext() != "CLOSE")
		{
			m_sceneManager->SwitchScene(m_sceneManager->GetCurrentScene()->CheckNext());
		}
		else
		{
			m_running = false;
		}
	}
	m_sceneManager->Update(dt);
}

void Game::Render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_sceneManager->Render();
	
  // SDL_GL_SwapWindow(m_Window);
}

void Game::HandleEvents(float dt)
{
	m_sceneManager->HandleInput(dt);
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::CleanUp()
{
	delete (m_sceneManager);
	m_sceneManager = nullptr;

	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	SDL_Quit();
}

