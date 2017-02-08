//other
#include "GameScene.h"

GameScene::GameScene(float width,float height) : Scene(Scenes::GAME),width(width),height(height)
{
	m_skyBox.createSkybox();
	// Camera
	cam = camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	texturedCube = Model("..\\ArgoDriver\\Assets\\Models\\cube.obj");
	texturedCone = Model("..\\ArgoDriver\\Assets\\Models\\cone.obj");
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
	texturedCube.Draw(cam);
	texturedCone.Draw(cam);
}