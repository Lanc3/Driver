#include <iostream>
#include <string>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Game.h"

using namespace std;

int main(int argc, char** argv){
	Game* game = new Game();
	glfwInit();
	game->Initialize();
	
	GLfloat currentTime;
	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;
	GLfloat fps = 1.f / 60.f;
	GLfloat step = 0;

	while(game->IsRunning())
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		game->HandleEvents(deltaTime);
		game->Update(deltaTime);
		game->Render();
	}
	
	game->CleanUp();
	
	return 0;
}


