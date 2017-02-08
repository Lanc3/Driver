//other
#include "GameScene.h"

GameScene::GameScene(float width,float height) : Scene(Scenes::GAME),width(width),height(height)
{
	m_skyBox.createSkybox();
	// Camera
	cam = camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	nanoSuit = Model("..\\ArgoDriver\\Assets\\Models\\nanosuit.obj");
	cylinder = Model("..\\ArgoDriver\\Assets\\Models\\cylinder.obj");
}

void GameScene::enter()
{

}
void GameScene::exit()
{

}

void GameScene::cleanUpRecources()
{
}

void GameScene::updateInput(float dt, unsigned char key, GLfloat xoffset, GLfloat yoffset)
{
	cam.ProcessInput(dt, key,  xoffset,  yoffset);
}


void GameScene::update(GLfloat dt)
{
}

void GameScene::draw()
{
	m_skyBox.render(cam, width, height);
	nanoSuit.Draw(cam, width, height);
	cylinder.Draw(cam, width, height);
}