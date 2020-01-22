#include "Scene.h"

Scene::Scene(string name) {
	m_name = name;
	m_active = true;
	m_alive = true;
	m_inputManager = InputManager::GetInstance();
	m_inputManager->ProcessInput();
	SoundEngine = createIrrKlangDevice();
}

Scene::~Scene() {}

void Scene::Start() { m_active = true; }

void Scene::Stop() { m_active = false; }

void Scene::SetDead(string name)
{ 
	m_alive = false;
	m_transition = name;
}

void Scene::SetAlive()
{
	m_alive = true;
	m_transition = "";
}

bool Scene::CheckDead()
{
	return m_alive;
}

string Scene::CheckNext()
{
	return m_transition;
}

std::string Scene::GetName() { return m_name; }
