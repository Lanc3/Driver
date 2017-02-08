
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include<string>

#include <GL/glew.h>
#include <vector>
#include <assimp/Importer.hpp>
#include<assimp/material.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL.h>
#include "Shader.h"
#include "Mesh.h"


using namespace std;

struct MeshData {
	string name;
	vector<Texture> textures;
	vector<Vertex> vertexes;
	vector<GLuint> indices;
};



class ResourceManager
{
public:
	ResourceManager() { }

	vector<Mesh> meshes;
	string directory;

	static std::map<std::string, Shader> shaders;
	MeshData meshData;
	//static std::map<std::string, MeshData> meshMap;
	static std::map<std::string, Mesh> madeMeshes;

	static Shader LoadShader(const GLchar* vShaderFile, const GLchar *fShaderFile, const GLchar * gShaderFile, std::string name);
	static Shader GetShader(string name);

	void LoadMeshes(std::string pat, string name);

	void LoadModel(string path, string name);
	vector<Texture> textures_loaded;

	void processNode(aiNode * node, const aiScene * scene, string name);

	Mesh processMesh(aiMesh * mesh, const aiScene * scene, string name);

	//static void LoadMeshes(std::string name);
	//static Mesh GetMesh(string name);

	void BuildMesh(string name);

	Mesh GetMesh(string name);

	static void Clear();

private:


	//ModelLoader loader;

	//static Shader loadMeshFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName);
	GLint textureFromFile(const char * path, string directory);
};

#endif