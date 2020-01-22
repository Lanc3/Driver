#pragma once
#include "Scene.h"
#include "SkyBox.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Model.h"
#include "Camera.h"
#include "Line.h"
#include "LevelManager.h"
#include "Player.h"
#include "PointLight.h"
#include "DirectionalLight.h"

#include "Components.h"
#include "RenderSystem.h"
#include "ControllerSystem.h"
#include "TransformSystem.h"
#include "CameraSystem.h"

#include "CollisionManager.h"
#include "PolygonBoundsSystem.h"
#include "MapCollisionSystem.h"
#include "CheckpointSystem.h"
#include "PickUpSystem.h"
#include "SAT\CollisionManager.h"
#include "PolygonBoundsSystem.h"
#include "AIMovementSystem.h"
#include "MultiplayerSystem.h"
#include "ControllerSystem.h"
#include "Net.h"

#include <vector>

struct LapData {
	string name;
	int lapTime;
	int lapCount;
};

class GameScene : public Scene
{
public:
	GameScene(SDL_Window * window);
	~GameScene();

	void Start();
	void Pause();
	void Exit();
	void ExitControls();

	void Update(float dt);
	void Render();
	void HandleInput(float dt);

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
	const int SCREENWIDTH = 1280;
	const int SCREENHEIGHT = 720;

	static std::map<GLchar, Character> Characters;

	vector<Entity*>m_players;
	vector<LapData>m_leaderboard;
	vector<string>m_message;
	Skybox m_sky;
	
	Entity * m_enemy;
	Entity * m_civOne;
	Entity * m_civTwo;

	int m_playerCount;

	Entity* m_checkPoint;
	Entity* m_pickUp;

	ISound* m_bgmGame;
	ISound* m_engineEffect;
	float engineVol;

	GLuint VAO;
	GLuint VBO;
	Shader m_textShader;
	Vector2f stickVector;

	MultiplayerSystem m_multiplayerSystem;
	RenderSystem m_renderSystem;
	TransformSystem m_transformSystem;
	ControllerSystem m_controllerSystem;
	CameraSystem m_cameraSystem;
	PolygonBoundsSystem m_polygonBoundsSystem;
	CheckpointSystem m_checkpointSystem;
	MapCollisionSystem m_mapCollisionSystem;
	AIMovementSystem m_AIMovementSystem;
	PickupSystem m_pickUpSystem;

	Camera* m_cam;

	int lapTimer;
	bool scoreboard = false;
	int scoreBoardY = 600;
	int maxLaps = 3;

	Shader m_lightingShader;
	DirectionalLight m_directionalLight;
	vector<PointLight> m_pointLights;
	std::vector<glm::vec3> objectPositions;
	std::vector<glm::vec3> lightPositions;
	std::vector<glm::vec3> lightColors;
	
	LevelManager m_levelManager;
	SDL_Window *m_window;

	void InitEntities();
	void InitSystems();

	Net* m_net = Net::GetInstance();

};