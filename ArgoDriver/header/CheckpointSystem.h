#pragma once

#include "System.h"
#include "Components.h"
#include "CollisionManager.h"
#include "LevelManager.h"
#include "Net.h"

#include <vector>

class CheckpointSystem : public System {
public:
	CheckpointSystem();
	~CheckpointSystem();

	void Update(float dt);
	void AddCheckpoint(Entity* e);

	int GetLaps();
private:
	CollisionManager m_collisionMgr;
	LevelManager m_levelMgr;

	int lapCount = 0;
	int checkpointIndex = 0;
	int checkpointSize = 0;

	Net* m_net;
	std::vector<Entity*> m_checkpoints;
};