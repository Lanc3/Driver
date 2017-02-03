#pragma once

#include "Scene.h"
#include "Shader.h"

enum class GAME_STATE {PAUSED, GAME, GAME_LOSE, GAME_WIN};
class GameScene : public Scene
{
public:
	GameScene();
	void update(float dt) override;
	void draw() override;
	void updateInput() override;
	int i = 0;
	//can be overrided
	void enter()override;
	void exit()override;

	void cleanUpRecources() override;
	//void exit();
private:
	GLuint VBO, VAO;
};
