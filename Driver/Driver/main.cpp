#include <iostream>

// GLEW
#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>

//glut 
#include <GL\glut.h>

// GLFW
#include <GLFW/glfw3.h>



// Other includes
#include "Shader.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void loadAssets();
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Driver", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);


	

	float old_t = glutGet(GLUT_ELAPSED_TIME);
	float dt = 0;//delta time
	float ct = 0;
	loadAssets();
	 // Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		//calculate delta time
		ct = glutGet(GLUT_ELAPSED_TIME);
		dt = (ct - old_t) / 1000.0;
		old_t = ct;
		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		//other updates
		SceneManager::getInstance()->update(dt);
		SceneManager::getInstance()->updateInput();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	//this loops through all the scenes and clears any recources that where created in them and releases them
	SceneManager::getInstance()->cleanUpRecources();
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		SceneManager::getInstance()->switchTo(Scenes::GAME);
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		SceneManager::getInstance()->switchTo(Scenes::MAINMENU);
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		SceneManager::getInstance()->switchTo(Scenes::GAME_LOSE);
	}
}

void loadAssets()
{
	SceneManager::getInstance()->addScene(new GameScene());
	SceneManager::getInstance()->addScene(new GameOverScene());
	SceneManager::getInstance()->addScene(new MainMenuScene());
	SceneManager::getInstance()->switchTo(Scenes::GAME);
}