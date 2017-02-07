#pragma once
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include "SOIL.h"
#include "Shader.h"
#include <vector>
#include "camera.h"

using namespace std;

class Skybox
{
public:
	void createSkybox();
	void render(camera cam);
	GLuint loadCubemap(vector<const GLchar*> faces);
	GLuint cubemapTexture;
	GLuint skyboxVAO;
	Shader m_shader;	
};