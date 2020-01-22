#pragma once

#include "Entity.h"
#include "Components.h"

#include <SDL.h>
#include <iostream> 
#include <math.h>

#include <vector>

class System {
public:
	System() {}
	~System() {}

	virtual void Update(float dt) = 0;

	void AddEntity(Entity* e) { m_entities.push_back(e); }
	void RemoveEntity(Entity* e) 
	{
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), e), m_entities.end());
	}
protected:
	std::vector<Entity*> m_entities;
};