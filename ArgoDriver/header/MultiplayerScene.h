#pragma once

#include "Scene.h"
#include "SDL_ttf.h"
#include "ResourceManager.h"
#include "Net.h"

class MultiplayerScene : public Scene
{
public:
	MultiplayerScene(SDL_Renderer* renderer);
	~MultiplayerScene();

	void Update(float dt);
	void Render();
	void HandleInput(float dt);

private:
	void CheckMessageConditions();
	void ConnectToServer();

	void LoadTextures();
	void BindKeys();

	void Return();
	void ScrollUp();
	void SetHighlight();
	void ScrollDown();
	void SelectKey();

	void Start();
	void Stop();

	Net* m_net = Net::GetInstance();

	SDL_Texture* JoinText;
	SDL_Texture* ConnectText;

	SDL_Texture* background;
	SDL_Texture* buttonJoin;
	SDL_Texture* buttonConnect;
	SDL_Texture* highlightTex;
	SDL_Texture* buttonReturn;

	SDL_Rect highlightTexr;
	SDL_Surface *text1;
	SDL_Color text_color;

	SDL_Rect backgroundPos;
	SDL_Rect buttonConnectPos;
	SDL_Rect buttonReturnPos;
	SDL_Rect buttonJoinPos;

	SDL_Rect JoinTextPos;
	SDL_Rect ConnectTextPos;

	SDL_Renderer* sdl_renderer;

	int JOYSTICK_DEADZONE = 10000;

	SDL_Event e;
	SDL_Joystick* gGameController = NULL;

	int m_selectedOption;
	bool m_joined;
};

