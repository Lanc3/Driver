#include "game.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"



Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
	
}

Game::~Game()
{

}

void Game::LoadResources()
{
	//Load Shaders
	Shader skyShader = ResourceManager::LoadShader("..\\ArgoDriver\\Shaders\\skyBoxShader.vs", "..\\ArgoDriver\\Shaders\\skyBoxShader.frag", nullptr, "skybox");
	Shader modelShader = ResourceManager::LoadShader("..\\ArgoDriver\\Shaders\\texture.vs", "..\\ArgoDriver\\Shaders\\texture.frag", nullptr, "model");
	Shader cubeShader = ResourceManager::LoadShader("..\\ArgoDriver\\Shaders\\texture.vs", "..\\ArgoDriver\\Shaders\\texture.frag", nullptr, "cube");


	Textures tex = ResourceManager::LoadTexture("..\\ArgoDriver\\ArgoDriver\\Assets\\Models\\testTexture.jpg", false, "testTexture");

	//Load Models
	ResourceManager manager;
	manager.LoadModel("..\\ArgoDriver\\Assets\\Models\\cube.obj", "cube");


}

void Game::Init()
{
	//LoadResources();

	SceneManager::getInstance()->addScene(new GameScene(Width,Height));
	SceneManager::getInstance()->addScene(new GameOverScene());
	SceneManager::getInstance()->addScene(new MainMenuScene());
	SceneManager::getInstance()->switchTo(Scenes::GAME);


	LoadResources();
}

void Game::Update(GLfloat dt)
{
	//other updates
	SceneManager::getInstance()->update(dt);
	
}


void Game::ProcessInput(GLfloat dt, unsigned char e, GLfloat xoffset, GLfloat yoffset)
{
	SceneManager::getInstance()->updateInput(dt,e,  xoffset,  yoffset);
}

void Game::Render()
{
	SceneManager::getInstance()->draw();
}