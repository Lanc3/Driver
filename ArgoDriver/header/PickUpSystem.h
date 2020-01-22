#pragma once

#include "System.h"
#include "Entity.h"
#include "Components.h"
#include <vector>

class PickupSystem : public System {
public:
	PickupSystem();
	~PickupSystem();
	void Update(float dt);
	Entity * CreatePickupPoint(glm::vec3 position);
	void CheckForCollisions(Entity* entity);
	void CreateMissile(Entity* player);
	Entity * CreateMine(Entity* player);
	void AddEntity(Entity * entity);	
private:
	void Homing(float dt);
	void Explode(Entity* bomb, Entity* victim);
	int m_sineWaveIndex = 0;
	void AnimatePickupSpawner(Entity * e, float dt);
	void ReleaseEntity(Entity * e);
};