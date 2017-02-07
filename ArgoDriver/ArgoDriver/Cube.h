#pragma once
#include <stdio.h>
#include <string>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <SOIL.h>
#include "camera.h"

using namespace std;
class Cube
{
public:
	Cube(string texture,glm::mat4 projection);
	Cube();
	~Cube();
	void update(float dt);
	void draw(camera cam);
	void clear();
private:
	string m_texturePath;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	Shader ourShader;
	GLuint VBO, VAO, EBO;
	// Load and create a texture
	GLuint texture1;
	GLuint texture2;
};

