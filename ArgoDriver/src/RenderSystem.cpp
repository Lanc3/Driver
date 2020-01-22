#include "RenderSystem.h"

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{
	
}

void RenderSystem::Draw(Camera* cam, Shader shader)
{
	if (!m_entities.empty())
	{
		for (Entity* e : m_entities)
		{
			Transformable* t = (Transformable*)e->GetComponent("transformable");
			ModelMesh* mM = (ModelMesh*)e->GetComponent("modelMesh");
			IDTag * ID = (IDTag*)e->GetComponent("IDTag");
			if (mM != nullptr)
			{
				LimitPitch(t);
				LimitBanking(t);

				mM->m_model.setPosition(t->m_position);
				mM->m_model.setRotation(glm::vec3(0, 1, 0), t->m_yaw + (PI / 2), t->m_bank, t->m_pitch);

				mM->m_model.Update();
				mM->m_model.Draw(cam, shader);
			}
		}
	}
}

void RenderSystem::LimitBanking(Transformable* t)
{
	if (t->m_bank > 0)
	{
		t->m_bank = t->m_bank - 0.01;
	}
	else if (t->m_bank < 0)
	{
		t->m_bank = t->m_bank + 0.01;
	}
	if (t->m_bank > 0.3f)
	{
		t->m_bank = 0.299f;
	}
	else if (t->m_bank < -0.3f)
	{
		t->m_bank = -0.299f;
	}
}

void RenderSystem::LimitPitch(Transformable* t)
{
	if (t->m_pitch > 0)
	{
		t->m_pitch = t->m_pitch - 0.001;
	}
	else if (t->m_pitch < 0)
	{
		t->m_pitch = t->m_pitch + 0.001;
	}

	if (t->m_pitch > 0.08f)
	{
		t->m_pitch = 0.079f;
	}
	else if (t->m_pitch < -0.08f)
	{
		t->m_pitch = -0.079f;
	}
}

void RenderSystem::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);
}