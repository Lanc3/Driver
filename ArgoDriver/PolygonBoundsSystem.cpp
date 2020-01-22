#include "PolygonBoundsSystem.h"



PolygonBoundsSystem::PolygonBoundsSystem()
{
}



PolygonBoundsSystem::~PolygonBoundsSystem()
{
}

void PolygonBoundsSystem::Update(float dt)
{
	for (auto & itr : m_entities) {
		PolygonBounds* p = (PolygonBounds*)itr->GetComponent("polygonBounds");
		if (p != nullptr)
		{
			p->m_bounds->Update(dt);
		}
	}
}

void PolygonBoundsSystem::Draw(Camera * cam)
{
	for (auto & itr : m_entities) {
		PolygonBounds* p = (PolygonBounds*)itr->GetComponent("polygonBounds");
		if (p != nullptr)
		{
			p->m_bounds->Draw(cam);
		}
	}
}

void PolygonBoundsSystem::AddEntity(Entity * e)
{
	m_entities.push_back(e);
}
//must add string name ang return component
void PolygonBoundsSystem::SetPosition(glm::vec3 position)
{
	for (auto & itr : m_entities) {
		PolygonBounds* p = (PolygonBounds*)itr->GetComponent("polygonBounds");
		if (p != nullptr)
		{
			p->m_bounds->SetPosition(position);
		}
	}
}
