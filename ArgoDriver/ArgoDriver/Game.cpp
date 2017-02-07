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

void Game::Init()
{
	SceneManager::getInstance()->addScene(new GameScene(Width,Height));
	SceneManager::getInstance()->addScene(new GameOverScene());
	SceneManager::getInstance()->addScene(new MainMenuScene());
	SceneManager::getInstance()->switchTo(Scenes::GAME);
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