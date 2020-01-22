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
#include <algorithm>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
public:
	Mesh() {};

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec4 actualMinPoint;
	glm::vec4 actualMaxPoint;
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	void calculateMinAndMax();
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void Draw(Camera* cam ,Shader shader);

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	
	bool emissionMap = false;
	bool normalMap = false;
	bool specularMap = false;

	void setupMesh();
};