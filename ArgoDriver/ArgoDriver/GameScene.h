#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Skybox.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class GAME_STATE {PAUSED, GAME, GAME_LOSE, GAME_WIN};
class GameScene : public Scene
{
public:
	GameScene(float width,float height);
	void update(GLfloat dt) override;
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
	GLuint VBO, VAO, EBO;
	//Render flag
	bool gRenderQuad = true;
	// Load and create a texture
	GLuint texture1;
	GLuint texture2;
	Shader ourShader;
	glm::mat4 trans;
	float width, height;
	Skybox m_skyBox;
};
