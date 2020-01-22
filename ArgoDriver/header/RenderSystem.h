#pragma once

#include "Components.h"
#include "Entity.h"
#include "Camera.h"

#include <vector>

class RenderSystem {
public:
	RenderSystem();
	~RenderSystem();

	void Draw(Camera* cam, Shader shader);
	void LimitBanking(Transformable * t);
	void LimitPitch(Transformable * t);
	void AddEntity(Entity* entity);

private:
	std::vector<Entity*> m_entities;
};