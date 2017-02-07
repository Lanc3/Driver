#pragma once
#include "Scene.h"


using namespace std;

class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	void createUIElements();
	void update(float dt) override;
	void draw() override;
	void updateInput(float dt, unsigned char key, GLfloat xoffset, GLfloat yoffset) override;

private:
	
};
