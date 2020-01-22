#include "LightingSystem.h"

LightingSystem::LightingSystem() : System()
{
}

LightingSystem::~LightingSystem()
{
}

Entity * LightingSystem::AddLight(
	glm::vec3 position,
	glm::vec3 direction,
	float radius,
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular,
	aiColor3D colour
	)
{
	Entity * entity;
	entity = new Entity("light");

	//only add transformable if it has a position, the game will not position point/spotlights at 0 0 0
	//direction lights do not care about position
	if (position != glm::vec3(0))
	{
		entity->AddComponent(new Transformable(position, 0, 0, 0));
	}

	entity->AddComponent(new LightSource(position, direction, radius, ambient, diffuse, specular, colour));
	
	m_entities.push_back(entity);
	return entity;
}