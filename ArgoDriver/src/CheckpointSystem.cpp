#include "CheckpointSystem.h"

CheckpointSystem::CheckpointSystem()
{
	m_levelMgr = LevelManager();
	m_net = Net::GetInstance();
	m_collisionMgr = CollisionManager();
}

CheckpointSystem::~CheckpointSystem()
{

}

void CheckpointSystem::Update(float dt)
{
	for (Entity* e : m_entities)
	{
		Transformable* t = (Transformable*)e->GetComponent("transformable");
		PolygonBounds* pB = (PolygonBounds*)e->GetComponent("polygonBounds");

		for (Entity* checkpts : m_checkpoints)
		{
			PolygonBounds* pBCheckpoint = (PolygonBounds*)checkpts->GetComponent("polygonBounds");
			CollisionData cd = m_collisionMgr.SATForConvex(*pBCheckpoint->m_bounds, *pB->m_bounds, t->m_direction);

			if (cd.isColliding)
			{
				if (checkpointIndex == m_levelMgr.listOfCheckpoints.size() - 1)
				{
					lapCount++;
					std::ostringstream oss;
					oss << "Lap Count : " << lapCount;
					std::cout << oss.str() << std::endl;
					checkpointIndex = 0;
				}
				else
					checkpointIndex++;
			}
			Transformable* tcheckpoint = (Transformable*)checkpts->GetComponent("transformable");
			tcheckpoint->m_position = m_levelMgr.listOfCheckpoints.at(checkpointIndex) + glm::vec3(0, 6, 0);
		}
	}
	if (m_net->IsConnected() && lapCount == 3)
	{
		m_net->Send("gameover");
	}
}

void CheckpointSystem::AddCheckpoint(Entity* e)
{
	m_checkpoints.push_back(e);
}

int CheckpointSystem::GetLaps()
{
	return lapCount;
}
