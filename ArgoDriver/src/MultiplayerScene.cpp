#include "MultiplayerScene.h"

MultiplayerScene::MultiplayerScene(SDL_Renderer * renderer) : Scene("Multiplayer")
{
	sdl_renderer = renderer;
	LoadTextures();
	
	m_joined = false;
	SDL_Init(SDL_INIT_JOYSTICK);
	gGameController = SDL_JoystickOpen(0);

}

MultiplayerScene::~MultiplayerScene()
{

}

void MultiplayerScene::Start()
{
	//if (m_inputManager->IsControllerConnected())
	//{
	BindKeys();
	m_selectedOption = 1;
	highlightTexr.x = 375;
	highlightTexr.w = 400;
	highlightTexr.h = 120;
	SetHighlight();
	//}
}

void MultiplayerScene::Stop()
{
	m_inputManager->EmptyKeys();
}

void MultiplayerScene::BindKeys()
{
	Command* select = new SpaceCommand(std::bind(&MultiplayerScene::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);

	Command* up = new SpaceCommand(std::bind(&MultiplayerScene::ScrollUp, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_UP, up, this);

	Command* down = new SpaceCommand(std::bind(&MultiplayerScene::ScrollDown, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_DOWN, down, this);

	Command* back = new SpaceCommand(std::bind(&MultiplayerScene::Return, this), Press);
	m_inputManager->AddKey(Event::BUTTON_B, back, this);
}

void MultiplayerScene::Return()
{
	this->SetDead("Menu");
}

void MultiplayerScene::ScrollUp()
{
	if (m_selectedOption >= 2)
	{
		m_selectedOption -= 1;
	}
	else if (m_selectedOption == 1)
	{
		m_selectedOption = 3;
	}
	SetHighlight();
}

void MultiplayerScene::SetHighlight()
{
	if (m_selectedOption == 1)
	{
		highlightTexr.x = 375;
		highlightTexr.w = 400;
		highlightTexr.h = 120;
		highlightTexr.y = 185;
	}
	else if (m_selectedOption == 2)
	{
		highlightTexr.x = 375;
		highlightTexr.w = 400;
		highlightTexr.h = 120;
		highlightTexr.y = 380;
	}
	else if (m_selectedOption == 3)
	{
		highlightTexr.y = 640;
		highlightTexr.x = -15;
		highlightTexr.w = 70;
		highlightTexr.h = 70;
	}
}

void MultiplayerScene::ScrollDown()
{
	if (m_selectedOption < 3)
	{
		m_selectedOption += 1;
	}
	else if (m_selectedOption == 3)
	{
		m_selectedOption = 1;
	}
	SetHighlight();
}

void MultiplayerScene::SelectKey()
{
	if (m_selectedOption == 1)
	{
		if (m_net->IsConnected() == false)
		{
			m_net->SetConnected(m_net->Init("34.251.26.78", 5228, 5229));
		}
	}
	else if (m_selectedOption == 2)
	{
		ConnectToServer();
	}
	else if (m_selectedOption == 3)
	{
		this->SetDead("Menu");
	}
}

void MultiplayerScene::Update(float dt)
{
	CheckMessageConditions();
}

void MultiplayerScene::CheckMessageConditions()
{
	vector<string> message;
	if (m_net->CheckForData())
		message = m_net->GetMessage();
	if (!message.empty())
	{
		if (message[0] == "start")
		{
			m_net->SetNoOfPlayers(atoi(message[2].c_str()));
			this->SetDead("Game");
		}
	}
}

void MultiplayerScene::ConnectToServer()
{
	if (m_net->IsConnected() == true)
	{
		if (!m_joined)
		{
			m_net->Send("join");
			m_joined = true;
		}
	}
}

void MultiplayerScene::LoadTextures()
{
	background = ResourceManager::getInstance()->GetTexture("MenuBackground");
	backgroundPos = ResourceManager::getInstance()->GetTextureRect("MenuBackground");

	buttonConnect = ResourceManager::getInstance()->GetTexture("ConnectButtonMP");
	buttonConnectPos = ResourceManager::getInstance()->GetTextureRect("ConnectButtonMP");

	buttonJoin = ResourceManager::getInstance()->GetTexture("MenuButtonMP");
	buttonJoinPos= ResourceManager::getInstance()->GetTextureRect("MenuButtonMP");

	ConnectText = ResourceManager::getInstance()->GetText("connectTextMP");
	ConnectTextPos = ResourceManager::getInstance()->GetTextRect("connectTextMP");

	JoinText = ResourceManager::getInstance()->GetText("JoinTextMP");
	JoinTextPos = ResourceManager::getInstance()->GetTextRect("JoinTextMP");

	buttonReturn = ResourceManager::getInstance()->getInstance()->GetTexture("ReturnButton");
	buttonReturnPos= ResourceManager::getInstance()->getInstance()->GetTextureRect("ReturnButton");

	highlightTex = ResourceManager::getInstance()->GetTexture("highlight");
}

void MultiplayerScene::Render()
{
	SDL_RenderClear(sdl_renderer);

	SDL_RenderCopy(sdl_renderer, background, NULL, &backgroundPos);
	SDL_RenderCopy(sdl_renderer, highlightTex, NULL, &highlightTexr);
	SDL_RenderCopy(sdl_renderer, buttonReturn, NULL, &buttonReturnPos);
	SDL_RenderCopy(sdl_renderer, buttonJoin, NULL, &buttonJoinPos);
	SDL_RenderCopy(sdl_renderer, buttonConnect, NULL, &buttonConnectPos);
	SDL_RenderCopy(sdl_renderer, JoinText, NULL, &JoinTextPos);
	SDL_RenderCopy(sdl_renderer, ConnectText, NULL, &ConnectTextPos);

	SDL_RenderPresent(sdl_renderer);
}

void MultiplayerScene::HandleInput(float dt)
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