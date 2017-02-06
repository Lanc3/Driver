#pragma once

#include "Scene.h"

using namespace std;

class GameOverScene : public Scene
{
public:
	GameOverScene();
	void update(float dt) override;
	void draw() override;
	void updateInput() override;
	//can be overrided
	//void exit();
	//void enter();

private:
	
};
