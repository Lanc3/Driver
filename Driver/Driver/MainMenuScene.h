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
	void updateInput() override;

private:
	
};
