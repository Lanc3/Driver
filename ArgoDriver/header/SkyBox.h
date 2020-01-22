#pragma once
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Other includes
#include <GL/glew.h>
#include "SOIL.h"
#include <vector>
#include "Camera.h"
#include "Shader.h"
#include "ResourceManager.h"

using namespace std;

class Skybox
{
public:
	void init();
	void render(Camera* cam, int screenWidth, int screenHeight);
	GLuint loadCubemap(vector<const GLchar*> faces);

private:
	GLuint m_cubemapTexture;
	GLuint m_VAO, m_VBO;
	Shader m_shader;
};