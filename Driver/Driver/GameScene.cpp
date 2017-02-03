// GLEW
#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>

//glut 
#include <GL\glut.h>

// GLFW
#include <GLFW/glfw3.h>

//other
#include "GameScene.h"

GameScene::GameScene()	:	Scene(Scenes::GAME)
{
	// Build and compile our shader program
	Shader ourShader("..\\Driver\\Shaders\\basic.vs", "..\\Driver\\Shaders\\basic.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions         // Colors
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top 
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
	ourShader.Use();
}

void GameScene::enter()
{
	
}
void GameScene::exit()
{
	
}

void GameScene::cleanUpRecources()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void GameScene::updateInput()
{

}

void GameScene::update(float dt)
{
	// Draw the triangle
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}



void GameScene::draw()
{
	
	
}

