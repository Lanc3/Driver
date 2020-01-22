#pragma once

// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include "camera.h"
#include <assimp/Importer.hpp>
#include<assimp/material.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include"ResourceManager.h"
#include "Mesh.h"
#include "Line.h"

class Model
{
public:
	Model();
	Model(string meshNameInResourceManager, glm::vec3 startingPosition,glm::vec3 scale,float rotation);
	void Update();
	Shader m_shader;
	bool shader;
	void setPosition(glm::vec3 pos);
	void setScale(glm::vec3 scale);
	void setRotationSpeed(float speed);
	void setRotation(glm::vec3 rotation, float speed, GLfloat m_bank, GLfloat m_pitch);
	//void setRotation(glm::vec3 rotation, float speed);
	void setRotation(glm::vec3 rotation);
	void Translate(glm::vec3 value);
	void Rotate(float angle);
	glm::mat4 model;
	void Draw(Camera* cam, Shader shader);

private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	glm::vec3 worldPosition;
	float worldRotationSpeed;
	glm::vec3 worldRotation;
	glm::vec3 worldScale = glm::vec3(1, 1, 1);
	
	GLfloat bank;
	GLfloat pitch;

	GLuint texture;
	glm::vec4 minModelPoint;
	glm::vec4 maxModelPoint;
	Line l;
	GLfloat	min_x, max_x, min_y, max_y, min_z, max_z;
	glm::vec3 size;
	glm::vec3 center;
	glm::mat4 transform;
	void MakeModel(string name);
};