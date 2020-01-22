#pragma once

#include "Entity.h"
#include "Components.h"
#include "Camera.h"

#include <vector>

class CameraSystem {
public:
	CameraSystem();
	CameraSystem(Camera* cam, Entity* target);
	~CameraSystem();
	
	void Chase(float dt);

private:
	Entity* m_target;
	Camera* m_camera;
};