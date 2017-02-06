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
	//Graphics program
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;
	GLuint VBO, VAO;
	//Render flag
	bool gRenderQuad = true;
};
