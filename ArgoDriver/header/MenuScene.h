#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"
#include "SDL_ttf.h"
#include "ResourceManager.h"
#include "Quad.h"

class MenuScene : public Scene 
{
public:
	MenuScene(SDL_Renderer * m_renderer);
	~MenuScene();

	void Update(float dt);
	void Render();
	void HandleInput(float dt);

	void Start();
	void Stop();

private:
	ISound* m_bgmMenu;

	SDL_Texture* menuTitle;
	SDL_Texture* play;
	SDL_Texture* options;
	SDL_Texture* quit;
	SDL_Texture* multi;

	SDL_Texture* img;
	SDL_Texture* buttonPlay;
	SDL_Texture* buttonMulti;
	SDL_Texture* buttonOpt;
	SDL_Texture* buttonQuit;
	SDL_Texture* highlightTex;

	SDL_Rect highlightTexr;
	SDL_Rect texr;
	SDL_Rect PlayTexr;
	SDL_Rect MultiTexr;
	SDL_Rect OptionsTexr;
	SDL_Rect QuitTexr;

	SDL_Rect menuTitlePos;
	SDL_Rect playPos;
	SDL_Rect optionPos;
	SDL_Rect quitPos;
	SDL_Rect multiPos;

	SDL_Event e;
	SDL_Joystick* gGameController = NULL;

	SDL_Renderer* sdl_renderer;

	int JOYSTICK_DEADZONE = 15000;
	int selectedOption; 
	void BindKeys();
	void ScrollUp();
	void SetHighlight();
	void ScrollDown();
	void SelectKey();
	void GetTextures();
	int timing = 0;

};

#endif // !MENUSCENE_H

