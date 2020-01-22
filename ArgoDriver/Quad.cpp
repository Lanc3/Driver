#include "Quad.h"


Quad::Quad() {}

Quad::Quad(glm::vec3 position,string textureName)
{
	TextureName = textureName;
	model = glm::mat4(1.0f);
	model = glm::translate(model,position)* glm::scale(model, glm::vec3(64,64,64));
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions          // Texture Coords
		1.0f,  0.0f, 1.0f,   1.0f, 1.0f, // Top Right
		1.0f, 0.0f, -1.0f,   1.0f, 0.0f, // Bottom Right
		-1.0f, 0.0f, -1.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  0.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	texture1 = ResourceManager::getInstance()->GetTextureID(TextureName);
}
void Quad::clear()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


Quad::~Quad()
{
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
}

void Quad::Update(float dt)
{
}

void Quad::Draw(Camera * cam, Shader shader)
{
	view = cam->GetViewMatrix();
	projection = glm::perspective(45.0f, (GLfloat)1280 / (GLfloat)720, 0.1f, 10000.0f);
	// Get their uniform location
	GLint modelLoc = glGetUniformLocation(shader.ID, "model");
	GLint viewLoc = glGetUniformLocation(shader.ID, "view");
	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	// Pass them to the shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shader.ID, "material.diffuse"), 0);

	// Set material properties
	glUniform1i(glGetUniformLocation(shader.ID, "specularMapping"), false);
	glUniform1i(glGetUniformLocation(shader.ID, "emissionMapping"), false);
	glUniform1i(glGetUniformLocation(shader.ID, "normalMapping"), false);
	glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"), 32.0f);

	// Draw container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}
