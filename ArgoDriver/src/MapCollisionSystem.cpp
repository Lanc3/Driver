#include "MapCollisionSystem.h"

MapCollisionSystem::MapCollisionSystem() : System()
{
	m_levelMgr = LevelManager();
	m_collisionMgr = CollisionManager();
}

MapCollisionSystem::~MapCollisionSystem()
{

}

void MapCollisionSystem::Update(float dt)
{
	for (Entity* e : m_entities)
	{
		Transformable* t = (Transformable*)e->GetComponent("transformable");
		PolygonBounds* pB = (PolygonBounds*)e->GetComponent("polygonBounds");
		Velocity* v = (Velocity*)e->GetComponent("velocity");
		IDTag * ID = (IDTag*)e->GetComponent("IDTag");
		for (auto & itr : m_levelMgr.GetMapObjects())
		{
			CollisionData d = m_collisionMgr.SATForConvex(itr->GetBounds(), *pB->m_bounds, t->m_direction);
			if (d.willCollide && itr->m_isCollidable)
			{
				if (v->m_acceleration > 0)
				{
					v->m_acceleration = v->m_acceleration / 2;
				}
				t->m_position += v->m_velocity - glm::vec3(d.MTV.x, 0, d.MTV.y);
				if (v->m_acceleration > 0.2f)
				{
					v->m_acceleration -= 0.01f;
				}
			}
			else
				t->m_position += v->m_velocity;
		}
		for (auto & itr : m_levelMgr.listOfPolygons)
		{
			CollisionData d = m_collisionMgr.SATForConvex(*itr, *pB->m_bounds, t->m_direction);
			if (d.willCollide)
			{
				if (v->m_acceleration > 0)
				{
					v->m_acceleration = v->m_acceleration *0.92;
				}
				t->m_position += v->m_velocity - glm::vec3(d.MTV.x, 0, d.MTV.y);
				if (v->m_acceleration > 0.2f)
				{
					v->m_acceleration -= 0.1f;
				}
			}
			else
				t->m_position += v->m_velocity;
		}
		/*if (ID->m_name == "player")
		{
			for (auto & itr : m_listOfobsticles)
			{
				PolygonBounds* p = (PolygonBounds*)itr->GetComponent("polygonBounds");
				CollisionData d = m_collisionMgr.SATForConvex(*p->m_bounds, *pB->m_bounds, t->m_direction);
				if (d.willCollide)
				{
					if (v->m_acceleration > 0)
					{
						v->m_acceleration -= 0.5;
					}
					t->m_position += v->m_velocity - glm::vec3(d.MTV.x, 0, d.MTV.y);
					if (v->m_acceleration > 0.2f)
					{
						v->m_acceleration -= 0.1f;
					}
				}
				else
					t->m_position += v->m_velocity;
			}
		}*/

	}
}
void MapCollisionSystem::AddObsticle(Entity * entity)
{
	m_listOfobsticles.push_back(entity);
}