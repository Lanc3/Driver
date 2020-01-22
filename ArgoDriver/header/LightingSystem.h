#pragma once

#include "System.h"
#include "Entity.h"
#include "Components.h"

#include <vector>

class LightingSystem : public System {
public:
	LightingSystem();
	~LightingSystem();

	//provide defaults so any light type can be used but only the relevant variables need to be set
	//Point Light: position, ambient, diffuse, specular, radius, colour
	//Direction Light: direction, ambient, diffuse, specular, colour
	//Spotlight: 
	Entity* AddLight(
		glm::vec3 position = glm::vec3(0),
		glm::vec3 direction = glm::vec3(0),
		float radius = 0,
		glm::vec3 ambient = glm::vec3(0),
		glm::vec3 diffuse = glm::vec3(0),
		glm::vec3 specular = glm::vec3(0),
		aiColor3D colour = aiColor3D(0, 0, 0)
	);

private:
};