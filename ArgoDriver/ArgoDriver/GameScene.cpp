//other
#include "GameScene.h"

GameScene::GameScene(float width,float height) : Scene(Scenes::GAME),width(width),height(height)
{
	m_skyBox.createSkybox();
	//testCube = Cube("", glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f));
	// Camera
	cam = camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	texturedCubeTest = Model("..\\ArgoDriver\\Assets\\Models\\cube.obj");
	cam = camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
	//testCube.draw(cam);
	texturedCubeTest.Draw(cam);
}

