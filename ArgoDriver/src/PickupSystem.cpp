#pragma once
#include "PickupSystem.h"

PickupSystem::PickupSystem() : System()
{
}

PickupSystem::~PickupSystem()
{
}

void PickupSystem::Update(float dt)
{
	for (Entity* e : m_entities)
	{
		for (int i = m_entities.size() - 1; i >= 0; i--)
		{
			if (m_entities[i]->GetAlive() == false)
			{
				m_entities.erase(m_entities.begin() + i);
			}
		}

		/*SeekingTarget* s = (SeekingTarget*)e->GetComponent("seekingtarget");

		if (s != NULL)
		{
			Homing(dt);
		}	*/

		if (e->GetName() == "pickupSpawner")
		{
			AnimatePickupSpawner(e, dt);
		}
	}	
}

void PickupSystem::AnimatePickupSpawner(Entity * e, float dt)
{
	Transformable * t = (Transformable*)e->GetComponent("transformable");
	t->m_yaw += 0.025f;
	t->m_roll += 0.05f; //no effect??
	//t->m_position.y *= sin(m_sineWaveIndex *(6.284 / 360.0)) * 1.75;

	//would be nice if the pickup model moved up and down over time
	/*m_sineWaveIndex++;
	if (m_sineWaveIndex > 360)
	{
		m_sineWaveIndex = 0;
	}*/
}

//basic sphere collision check
void PickupSystem::CheckForCollisions(Entity* entity)
{
	if (!m_entities.empty())
	{
		for (Entity* e : m_entities)
		{
			Transformable* t = (Transformable*)e->GetComponent("transformable");
			Collidable* c = (Collidable*)e->GetComponent("collidable");
			Explosive* explode = (Explosive*)e->GetComponent("explosive");
		
			if (t != NULL && c != NULL)
			{
				Collidable* otherc = (Collidable*)entity->GetComponent("collidable");
				Transformable* othert = (Transformable*)entity->GetComponent("transformable");
				if (otherc == NULL && othert != NULL) continue;

				float distance = sqrt(((t->m_position.x - othert->m_position.x)*(t->m_position.x - othert->m_position.x)) +
									  ((t->m_position.y - othert->m_position.y)*(t->m_position.y - othert->m_position.y)) +
									  ((t->m_position.z - othert->m_position.z)*(t->m_position.z - othert->m_position.z)));

				//collision responses
				if (distance <= c->m_radius + otherc->m_radius)
				{					
					if (explode != NULL)
					{
						Explode(e, entity);
					}
					else
					{
						
					}
				}
			}	
		}
	}	
}

void PickupSystem::Explode(Entity* bomb, Entity* victim)
{	
	Explosive* e = (Explosive*)bomb->GetComponent("explosive");
	Velocity* v = (Velocity*)victim->GetComponent("velocity");
	v->m_acceleration = -1; //push the player back, very basic response, not really applicable, ideally effected by bomb force vector	
}

void PickupSystem::Homing(float dt)
{

}

void PickupSystem::CreateMissile(Entity* player)
{
	//create a missile entity
	Transformable* t = (Transformable*)player->GetComponent("transformable");
	Entity* entity;
	entity = new Entity();
	entity->AddComponent(new ModelMesh("missile", t->m_position, glm::vec3(1, 1, 1), 0.f));
	entity->AddComponent(new Transformable(t->m_position, 0.f, 0.f, 0.f));
	entity->AddComponent(new Explosive(1.f, glm::vec3(0.f, 0.f, 0.f)));
	AddEntity(entity);
}

Entity * PickupSystem::CreateMine(Entity* player)
{
	//create a mine entity
	Transformable* t = (Transformable*)player->GetComponent("transformable");
	Entity* entity;
	entity = new Entity("mine");
	entity->AddComponent(new Collidable(3.f));
	entity->AddComponent(new ModelMesh("mine", t->m_position, glm::vec3(0.001f, 0.001f, 0.001f), 0.f));
	entity->AddComponent(new Transformable(t->m_position + glm::vec3(0.f,0.f,5.f), rand() % 180, 0.f, 0.f));
	entity->AddComponent(new Explosive(0.5f, glm::vec3(0.f, 1.f, 0.f))); //upward force
	return entity;	
}

Entity * PickupSystem::CreatePickupPoint(glm::vec3 position)
{
	//create a pickup spawner entity
	Entity* entity;
	entity = new Entity("pickupSpawner");
	entity->AddComponent(new Collidable(3.f));
	entity->AddComponent(new ModelMesh("pickupSpawner", glm::vec3(0), glm::vec3(0.1, 0.1, 0.1), 0.f));
	entity->AddComponent(new Transformable(position, 0.f, 0.f, 0.f));
	return entity;
}

void PickupSystem::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);
}

void PickupSystem::ReleaseEntity(Entity * e)
{
	//need a way for multiple systems to remove an entity, alive?
	e->SetAlive(false); 
	RemoveEntity(e);
}