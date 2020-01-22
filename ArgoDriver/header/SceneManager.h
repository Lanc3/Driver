#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL.h>
#include "Scene.h"

#include "MenuScene.h"
#include "GameScene.h"
#include "OptionsScene.h"
#include "GameOverScene.h"
#include "MultiplayerScene.h"

#include <vector>

using namespace std;

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	void Update(float dt);
	void Render();
	void HandleInput(float dt);

	void AddScene(Scene* scene);
	void SwitchScene(string name);
	void NextScene();
	void PreviousScene();

	Scene* GetCurrentScene();

private:
	MenuScene* m_menu;
	OptionsScene* m_options;
	GameScene* m_game;
	MultiplayerScene* m_multiplayer;
	GameOverScene* m_gameover;

	Scene* m_currScene;

	vector<Scene*> m_scenes;
};

#endif SCENEMANAGER_H
