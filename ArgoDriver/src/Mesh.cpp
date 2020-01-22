#include "Mesh.h"
#include "ResourceManager.h"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->textures = textures;
	this->indices = indices;
	this->setupMesh();
}

void Mesh::Draw(Camera* cam, Shader shader)
{
	view = cam->GetViewMatrix();
	projection = glm::perspective(45.0f, (GLfloat)1280 / (GLfloat)720, 0.1f, 10000.0f);

	// Get their uniform location
	GLint modelLoc = glGetUniformLocation(shader.ID, "model");
	GLint viewLoc = glGetUniformLocation(shader.ID, "view");
	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint viewPosLoc = glGetUniformLocation(shader.ID, "viewPos");
	glUniform3f(viewPosLoc, cam->GetPosition().x, cam->GetPosition().y, cam->GetPosition().z);

	//bind relevant textures
	for (int i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		string name = this->textures[i].type;
		if (name == "texture_diffuse")
		{
			glUniform1i(glGetUniformLocation(shader.ID, "material.diffuse"), i);
		}
		else if (name == "texture_specular")
		{
			specularMap = true;
			glUniform1i(glGetUniformLocation(shader.ID, "material.specular"), i);
		}
		else if (name == "texture_emissive")
		{
			emissionMap = true;
			glUniform1i(glGetUniformLocation(shader.ID, "material.emission"), i);
		}
		else if (name == "texture_bump")
		{
			normalMap = true;
			glUniform1i(glGetUniformLocation(shader.ID, "material.normalMap"), i);
		}

		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}

	// Set material properties
	glUniform1i(glGetUniformLocation(shader.ID, "specularMapping"), specularMap);
	glUniform1i(glGetUniformLocation(shader.ID, "emissionMapping"), emissionMap);
	glUniform1i(glGetUniformLocation(shader.ID, "normalMapping"), normalMap);
	glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"), 32.0f);

	//render model
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);	
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);

}
void Mesh::calculateMinAndMax()
{

}