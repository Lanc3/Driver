#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_currScene = nullptr;
}

SceneManager::~SceneManager()
{
	m_currScene = nullptr;
	for (int i = 0; i < m_scenes.size(); i++)
	{
		delete m_scenes.at(i);
		m_scenes.at(i) = nullptr;
	}
}

void SceneManager::Update(float dt) { m_currScene->Update(dt); }

void SceneManager::Render() { m_currScene->Render(); }

void SceneManager::HandleInput(float dt) { m_currScene->HandleInput(dt); }

void SceneManager::AddScene(Scene* scene)
{
	m_scenes.push_back(scene);
}

void SceneManager::SwitchScene(std::string name)
{
	cout << "Switching Scene" << endl;
	bool found = false;
	Scene* nextScene = nullptr;

	for (int i = 0; i < m_scenes.size() && !found; i++) 
	{
		if (m_scenes.at(i)->GetName() == name)
		{
			found = true;
			nextScene = m_scenes.at(i);
		}
	}

	if (found)
	{
		if (m_currScene != nullptr)
			m_currScene->Stop();

		if (nextScene->CheckDead() == false)
		{
			nextScene->SetAlive();
		}

		m_currScene = nextScene;
		m_currScene->Start();
	}
}

void SceneManager::NextScene()
{
	bool found = false;
	Scene* nextScene = nullptr;

	for (int i = 0; i < m_scenes.size() && !found; i++) 
	{
		if (m_scenes.at(i)->GetName() == m_currScene->GetName() && i + 1 < m_scenes.size())
		{
			found = true;
			nextScene = m_scenes.at(i + 1);
		}
	}

	if (found)
	{
		if (m_currScene != nullptr)
			m_currScene->Stop();

		m_currScene = nextScene;
		m_currScene->Start();
	}
}

void SceneManager::PreviousScene()
{
	bool found = false;
	Scene* nextScene = nullptr;

	for (int i = 0; i < m_scenes.size() && !found; i++)
	{
		if (m_scenes.at(i)->GetName() == m_currScene->GetName())
		{
			found = true;
			nextScene = m_scenes.at(i - 1);
		}
	}

	if (found)
	{
		if (m_currScene != nullptr)
			m_currScene->Stop();

		m_currScene = nextScene;
		m_currScene->Start();
	}
}


Scene* SceneManager::GetCurrentScene() { return m_currScene; }