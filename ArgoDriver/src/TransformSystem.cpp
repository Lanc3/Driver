#include "TransformSystem.h"

TransformSystem::TransformSystem()
{
	EffectEngine = createIrrKlangDevice();
	engine = EffectEngine->play2D("Assets\\audio\\loop.wav", GL_TRUE, GL_TRUE);
	engineVol = 0;
}

TransformSystem::~TransformSystem()
{

}

void TransformSystem::Update(float dt)
{
	m_timer += dt;
	engine->setVolume(engineVol);
	engine->setIsPaused(false);

	for (Entity* e : m_entities)
	{
		Transformable* t = (Transformable*)e->GetComponent("transformable");
		Velocity * v = (Velocity*)e->GetComponent("velocity");
		PolygonBounds* pB = (PolygonBounds*)e->GetComponent("polygonBounds");
		CircleBounds * cB = (CircleBounds*)e->GetComponent("circleBounds");
		IDTag * ID = (IDTag*)e->GetComponent("IDTag");
		if (v != nullptr)
		{
			t->m_direction = glm::normalize(glm::vec3(cos(-t->m_yaw), 0, sin(-t->m_yaw)));
			v->m_velocity = t->m_direction * (v->m_acceleration * 0.01f);
			//AIstuff
			t->m_dynamicLength = glm::length(v->m_velocity) / v->m_maxAcceleration;
			t->m_ahead = t->m_position + (v->m_velocity * t->m_dynamicLength);
			t->m_ahead2 = t->m_position + (v->m_velocity * (t->m_dynamicLength* 0.5f));
			if (m_timer >= .1f)
			{
				if (v->m_acceleration > 0.11f)
				{
					v->m_acceleration -= 0.01f;
					
				}
				m_timer = 0;
			}
			//t->m_position += v->m_velocity;
			engineVol = v->m_acceleration * 0.01f;
		}
		if (t != nullptr)
		{
			pB->m_bounds->SetPosition(t->m_position);
		}
		if (cB != nullptr)
		{
			cB->m_bounds->SetCenter(t->m_position);
		}
		
		//
	}
}

void TransformSystem::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);
}