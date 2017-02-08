#pragma once
// GLEW
#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>




#include <SOIL.h>
#include "camera.h"

#include "Model.h"

#include "Scene.h"
#include "Shader.h"
#include "Skybox.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cube.h"

enum class GAME_STATE {PAUSED, GAME, GAME_LOSE, GAME_WIN};
class GameScene : public Scene
{
public:
	GameScene(float width,float height);
	void update(GLfloat dt) override;
	void draw() override;
	void updateInput(float dt, unsigned char key, GLfloat xoffset, GLfloat yoffset) override;
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
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	Cube testCube;
	camera cam;
	Model myModel;
	Model texturedCubeTest;
};
