#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <GL\glew.h>
#include <iostream>

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Shader.h"

class Game
{
public:
	Game();
	~Game();
	bool Initialize();
	void LoadResources();

	void Update(float dt);
	void HandleEvents(float dt);
	void Render();
	bool IsRunning();
	void CleanUp();
private:
	void SetupScenes();

	bool SetOpenGLAttributes();
	SDL_GLContext m_context;
	bool m_running;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Surface* m_Surface;
	ResourceManager m_recMan;
	SceneManager* m_sceneManager;

};
#endif

