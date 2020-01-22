#pragma once

#include <iostream> 
#include <math.h>

#include "FLInputManager.h"
#include "irrKlang.h"

using namespace irrklang;
using namespace std;

class Scene : public EventListener
{
public:
	Scene(string name);
	~Scene();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void HandleInput(float dt) = 0;

	virtual void Start();
	virtual void Stop();

	void SetDead(string name);
	void SetAlive();
	bool CheckDead();
	string CheckNext();
	string GetName();

protected:
	ISoundEngine *SoundEngine;
	InputManager* m_inputManager;
	bool m_active;
	bool m_alive;
	string m_transition;
	string	m_name;
};
