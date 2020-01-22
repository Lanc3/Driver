#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* m_renderer) : Scene("Menu")
{
	GetTextures();
	sdl_renderer = m_renderer;

	SDL_Init(SDL_INIT_JOYSTICK);
	gGameController = SDL_JoystickOpen(0);

}

MenuScene::~MenuScene()
{

}

void MenuScene::Start()
{
	m_bgmMenu = SoundEngine->play2D("Assets\\audio\\music1.wav", GL_TRUE, GL_TRUE);
	m_bgmMenu->setVolume(0.3);

	//if (m_inputManager->IsControllerConnected())
	//{
	selectedOption = 1;
		//BindKeys();
	highlightTexr.x = 350;
	highlightTexr.w = 400;
	highlightTexr.h = 120;
	SetHighlight();
	//}
}

void MenuScene::Stop()
{
	m_inputManager->EmptyKeys();
}

void MenuScene::BindKeys()
{
	Command* select = new SpaceCommand(std::bind(&MenuScene::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);

	Command* up = new SpaceCommand(std::bind(&MenuScene::ScrollUp, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_UP, up, this);

	Command* down = new SpaceCommand(std::bind(&MenuScene::ScrollDown, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_DOWN, down, this);
}

void MenuScene::Update(float dt)
{
	m_bgmMenu->setIsPaused(false);
	timing += 1;

	if (timing > 100)
	{
	//	this->SetDead("Game");
	}
}

void MenuScene::ScrollUp()
{
	if (selectedOption >= 2)
	{
		selectedOption -= 1;
	}
	else if(selectedOption == 1)
	{
		selectedOption = 4;
	}
	SetHighlight();
}

void MenuScene::SetHighlight()
{
	if (selectedOption == 1)
	{
		highlightTexr.y = 135;
	}
	else if (selectedOption == 2)
	{
		highlightTexr.y = 285;
	}
	else if (selectedOption == 3)
	{
		highlightTexr.y = 435;
	}
	else if (selectedOption == 4)
	{
		highlightTexr.y = 585;
	}
}

void MenuScene::ScrollDown()
{
	if (selectedOption < 4)
	{
		selectedOption += 1;
	}
	else if (selectedOption == 4)
	{
		selectedOption = 1;
	}
	SetHighlight();
}

void MenuScene::SelectKey()
{
	if (selectedOption == 1)
	{
		m_bgmMenu->stop();
		this->SetDead("Game");
	}
	else if (selectedOption == 2)
	{
		this->SetDead("Multiplayer");
	}
	else if (selectedOption == 3)
	{
		this->SetDead("Options");
	}
	else if (selectedOption == 4)
	{
		this->SetDead("CLOSE");
	}
}

void MenuScene::GetTextures()
{
	img = ResourceManager::getInstance()->GetTexture("MenuBackground");
	texr = ResourceManager::getInstance()->GetTextureRect("MenuBackground");

	buttonPlay = ResourceManager::getInstance()->GetTexture("PlayButton");
	PlayTexr = ResourceManager::getInstance()->GetTextureRect("PlayButton");

	buttonMulti = ResourceManager::getInstance()->GetTexture("MPButton");
	MultiTexr = ResourceManager::getInstance()->GetTextureRect("MPButton");

	buttonOpt = ResourceManager::getInstance()->GetTexture("OptButton");
	OptionsTexr = ResourceManager::getInstance()->GetTextureRect("OptButton");

	buttonQuit = ResourceManager::getInstance()->GetTexture("QuitButton");
	QuitTexr = ResourceManager::getInstance()->GetTextureRect("QuitButton");
	
	menuTitle = ResourceManager::getInstance()->GetText("MenuTitle");
	menuTitlePos = ResourceManager::getInstance()->GetTextRect("MenuTitle");

	play = ResourceManager::getInstance()->GetText("PlayText");
	playPos = ResourceManager::getInstance()->GetTextRect("PlayText");

	multi = ResourceManager::getInstance()->GetText("MPText");
	multiPos = ResourceManager::getInstance()->GetTextRect("MPText");

	options = ResourceManager::getInstance()->GetText("OptionsText");
	optionPos = ResourceManager::getInstance()->GetTextRect("OptionsText");

	quit = ResourceManager::getInstance()->GetText("QuitText");
	quitPos= ResourceManager::getInstance()->GetTextRect("QuitText");

	highlightTex = ResourceManager::getInstance()->GetTexture("highlight");

}

void MenuScene::Render()
{
	SDL_RenderClear(sdl_renderer);
	
	SDL_RenderCopy(sdl_renderer, img, NULL, &texr);
	SDL_RenderCopy(sdl_renderer, highlightTex, NULL, &highlightTexr);
	SDL_RenderCopy(sdl_renderer, buttonPlay, NULL, &PlayTexr);
	SDL_RenderCopy(sdl_renderer, buttonMulti, NULL, &MultiTexr);
	SDL_RenderCopy(sdl_renderer, buttonOpt, NULL, &OptionsTexr);
	SDL_RenderCopy(sdl_renderer, buttonQuit, NULL, &QuitTexr);
	SDL_RenderCopy(sdl_renderer, menuTitle, NULL, &menuTitlePos);
	
	SDL_RenderCopy(sdl_renderer, multi, NULL, &multiPos);
	SDL_RenderCopy(sdl_renderer, play, NULL, &playPos);
	SDL_RenderCopy(sdl_renderer, options, NULL, &optionPos);
	SDL_RenderCopy(sdl_renderer, quit, NULL, &quitPos);
	SDL_RenderPresent(sdl_renderer);
}

void MenuScene::HandleInput(float dt)
{
	if (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_JOYAXISMOTION)
		{
			if (e.jaxis.axis == 1)
			{
				if (e.jaxis.value > JOYSTICK_DEADZONE)
				{
					ScrollDown();
				}
				else if (e.jaxis.value < -JOYSTICK_DEADZONE)
				{
					ScrollUp();
				}
			}
		}
		if (e.type == SDL_JOYBUTTONDOWN)
		{
			cout << e.button.which << endl;
			if (e.button.type == 1539)
			{
				SelectKey();
				cout << "HI" << endl;
			}
		}
	}

	m_inputManager->ProcessInput();
}

