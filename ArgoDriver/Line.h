#pragma once
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"

class Line
{
public:
	Line();
	Line(glm::vec3 start, glm::vec3 end);
	Line(glm::vec4 start, glm::vec4 end);
	Line(glm::vec3 start, glm::vec3 end, float thickness);
	Line(glm::vec4 start, glm::vec4 end, float thickness);
	~Line();
	void Update(float dt);
	void Draw(Camera * cam);
private:
	glm::vec3 startPosition;
	glm::vec3 endPosition;
	Shader shader;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	float lineThickness = 5;
};

