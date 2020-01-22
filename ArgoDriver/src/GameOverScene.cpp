#include "GameOverScene.h"

GameOverScene::GameOverScene(SDL_Renderer* m_renderer) : Scene("GameOver")
{
	GetTextures();
	sdl_renderer = m_renderer;
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Start()
{
	if (m_inputManager->IsControllerConnected())
	{
		BindKeys();
		selectedOption = 1;
		SetHighlight();
	}
}

void GameOverScene::Stop()
{
	m_inputManager->EmptyKeys();
}

void GameOverScene::Update(float dt)
{
	
}

void GameOverScene::BindKeys()
{
	Command* select = new SpaceCommand(std::bind(&GameOverScene::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);

	Command* up = new SpaceCommand(std::bind(&GameOverScene::ScrollUp, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_UP, up, this);

	Command* down = new SpaceCommand(std::bind(&GameOverScene::ScrollDown, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_DOWN, down, this);

	Command* back = new SpaceCommand(std::bind(&GameOverScene::Return, this), Press);
	m_inputManager->AddKey(Event::BUTTON_B, back, this);
}

void GameOverScene::Return()
{
	this->SetDead("Menu");
}

void GameOverScene::SelectKey()
{
	if (selectedOption == 1)
	{
		this->SetDead("Menu");
	}
	else if (selectedOption == 2)
	{
		this->SetDead("CLOSE");
	}
}

void GameOverScene::GetTextures()
{
	background =  ResourceManager::getInstance()->GetTexture("MenuBackground");
	texr =  ResourceManager::getInstance()->GetTextureRect("MenuBackground");

	buttonReturn =  ResourceManager::getInstance()->GetTexture("ReturnButtonGO");
	ReturnTexr =  ResourceManager::getInstance()->GetTextureRect("ReturnButtonGO");

	buttonQuit =  ResourceManager::getInstance()->GetTexture("QuitButtonGO");
	QuitTexr =  ResourceManager::getInstance()->GetTextureRect("QuitButtonGO");

	returnText =  ResourceManager::getInstance()->GetText("ReturnTextGO");
	returnTextTexr =  ResourceManager::getInstance()->GetTextRect("ReturnTextGO");

	quitText =  ResourceManager::getInstance()->GetText("QuitTextGO");
	quitTextTexr =  ResourceManager::getInstance()->GetTextRect("QuitTextGO");

	gameOverText =  ResourceManager::getInstance()->GetText("GameOverTitle");
	gameOverPos =  ResourceManager::getInstance()->GetTextRect("GameOverTitle");

	gameOverTitle =  ResourceManager::getInstance()->GetText("GameOverText");
	gameOverTitlePos =  ResourceManager::getInstance()->GetTextRect("GameOverText");

	hightlighttex = ResourceManager::getInstance()->GetTexture("highlight");
}


void GameOverScene::ScrollUp()
{
	if (selectedOption >= 2)
	{
		selectedOption -= 1;
	}
	else if (selectedOption == 1)
	{
		selectedOption = 4;
	}
	SetHighlight();
}

void GameOverScene::SetHighlight()
{
	if (selectedOption == 1)
	{
		highlightTexr.x = 375;
		highlightTexr.w = 400;
		highlightTexr.h = 135;
		highlightTexr.y = 275;
	}
	else if (selectedOption == 2)
	{
		highlightTexr.x = 375;
		highlightTexr.w = 400;
		highlightTexr.h = 135;
		highlightTexr.y = 475;
	}
}

void GameOverScene::ScrollDown()
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

void GameOverScene::Render()
{
	SDL_RenderClear(sdl_renderer);

	SDL_RenderCopy(sdl_renderer, background, NULL, &texr);
	SDL_RenderCopy(sdl_renderer, hightlighttex, NULL, &highlightTexr);
	SDL_RenderCopy(sdl_renderer, buttonReturn, NULL, &ReturnTexr);
	SDL_RenderCopy(sdl_renderer, buttonQuit, NULL, &QuitTexr);
	SDL_RenderCopy(sdl_renderer, returnText, NULL, &returnTextTexr);
	SDL_RenderCopy(sdl_renderer, quitText, NULL, &quitTextTexr);

	SDL_RenderCopy(sdl_renderer, gameOverText, NULL, &gameOverPos);
	SDL_RenderCopy(sdl_renderer, gameOverTitle, NULL, &gameOverTitlePos);

	SDL_RenderPresent(sdl_renderer);
}

void GameOverScene::HandleInput(float dt)
{
	m_inputManager->ProcessInput();
}

