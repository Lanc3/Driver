#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/types.h>
#include "Shader.h"
#include "camera.h"
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
public:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

	void Draw(Shader shader,camera cam, int screenWidth, int screenHeight);

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void setupMesh();
};