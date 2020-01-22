#pragma once

#include "Entity.h"
#include "Components.h"

#include <vector>

class PolygonBoundsSystem
{
public:
	PolygonBoundsSystem();
	~PolygonBoundsSystem();

	void Update(float dt);
	void Draw(Camera* cam);
	void AddEntity(Entity* e);
	void SetPosition(glm::vec3 position);

private:
	std::vector<Entity*> m_entities;
};

