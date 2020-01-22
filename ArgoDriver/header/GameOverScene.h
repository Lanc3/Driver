#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "Scene.h"
#include "SDL_ttf.h"
#include "ResourceManager.h"

class GameOverScene : public Scene
{
public:
	GameOverScene(SDL_Renderer * m_renderer);
	~GameOverScene();

	void Update(float dt); 
	void Render();
	void HandleInput(float dt);

	void Start();
	void Stop();

private:
	SDL_Texture* background;
	SDL_Texture* gameOverTitle;
	SDL_Texture* returnText;
	SDL_Texture* quitText;
	SDL_Texture* gameOverText;
	SDL_Texture* hightlighttex;

	SDL_Texture* buttonReturn;
	SDL_Texture* buttonQuit;

	SDL_Rect highlightTexr;
	SDL_Rect texr;
	SDL_Rect ReturnTexr;
	SDL_Rect returnTextTexr;
	SDL_Rect quitTextTexr;
	SDL_Rect QuitTexr;

	SDL_Rect gameOverTitlePos;
	SDL_Rect returnPos;
	SDL_Rect quitPos;

	SDL_Rect gameOverPos;

	SDL_Renderer* sdl_renderer;

	int selectedOption;

	void BindKeys();
	void Return();
	void SelectKey();
	void GetTextures();
	void ScrollUp();
	void SetHighlight();
	void ScrollDown();
	
};

#endif // !MENUSCENE_H

