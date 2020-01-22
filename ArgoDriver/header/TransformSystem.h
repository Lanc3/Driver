#pragma once

#include "Components.h"
#include "Entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "irrKlang.h"

#include <vector>
#include "Circle.h"

using namespace irrklang;

class TransformSystem {
public:
	TransformSystem();
	~TransformSystem();

	ISoundEngine *EffectEngine;
	ISound* engine;

	void Update(float dt);
	void AddEntity(Entity* entity);


private:
	std::vector<Entity*> m_entities;
	float m_timer = 0;
	float engineVol;
};