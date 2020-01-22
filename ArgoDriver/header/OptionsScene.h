#pragma once
#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include "Scene.h"
#include "SDL_ttf.h"
#include "ResourceManager.h"

class OptionsScene : public Scene
{
public:
	OptionsScene(SDL_Renderer * m_renderer);
	~OptionsScene();

	void Update(float dt);
	void Render();
	void HandleInput(float dt);
	
	void Start();
	void Stop();

private:
	SDL_Texture* optionsTitle;
	SDL_Texture* returnButton;
	SDL_Texture* audio;
	SDL_Texture* graphics;
	SDL_Texture* game;
	SDL_Texture* highlightTex;

	SDL_Texture* background;
	SDL_Texture* buttonAudio;
	SDL_Texture* buttonGraphics;
	SDL_Texture* buttonGame;

	SDL_Rect highlightTexr;
	SDL_Rect texr;
	SDL_Rect returnTexr;
	SDL_Rect AudioTexr;
	SDL_Rect GraphicsTexr;
	SDL_Rect GameTexr;

	SDL_Rect optionsTitlePos;
	SDL_Rect audioOptPos;
	SDL_Rect graphicsOptPos;
	SDL_Rect gameOptPos;

	SDL_Renderer* sdl_renderer;

	int selectedOption;
	int JOYSTICK_DEADZONE = 10000;

	SDL_Event e;
	SDL_Joystick* gGameController = NULL;

	void BindKeys();
	void Return();
	void SelectKey();
	void GetTextures();
	void ScrollUp();
	void SetHighlight();
	void ScrollDown();
};

#endif // !MENUSCENE_H

