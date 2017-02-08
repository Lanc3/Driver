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

class Model
{
public:
	Model() {}

	Model(GLchar* path);

	void GetMesh(string name);

	void Draw(camera cam, string name);

private:

	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	//Shader m_shader;
	
	//void LoadModel(string path);
	GLuint texture;
	//void processNode(aiNode* node, const aiScene* scene);

	//Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	//vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	//GLint textureFromFile(const char* path, string directory);
};