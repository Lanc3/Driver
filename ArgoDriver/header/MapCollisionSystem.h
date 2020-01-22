#pragma once

#include "System.h"
#include "Components.h"
#include "CollisionManager.h"
#include "LevelManager.h"

#include <vector>

class MapCollisionSystem : public System {
public:
	MapCollisionSystem();
	~MapCollisionSystem();

	void Update(float dt);
	void AddObsticle(Entity * entity);
private:

	CollisionManager m_collisionMgr;
	LevelManager m_levelMgr;
	vector<Entity*> m_listOfobsticles;
};