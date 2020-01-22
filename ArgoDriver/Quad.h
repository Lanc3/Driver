#pragma once
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"
#include "ResourceManager.h"

class Quad
{
public:
	Quad();
	Quad(glm::vec3 position,string textureName);
	void clear();
	~Quad();
	void Update(float dt);
	void Draw(Camera * cam, Shader shader);
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	GLuint VBO, VAO, EBO;
	GLuint texture1;
	string TextureName;
};

