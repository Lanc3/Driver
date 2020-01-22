#include "CameraSystem.h"

CameraSystem::CameraSystem()
{
	
}

CameraSystem::CameraSystem(Camera* cam, Entity* target)
{
	if (cam != NULL && target != NULL) 
	{
		m_camera = cam;
		m_target = target;
	}
}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::Chase(float dt)
{
	
	Transformable* t = (Transformable*)m_target->GetComponent("transformable");
	Velocity* v = (Velocity*)m_target->GetComponent("velocity");
	if (t != nullptr && v != nullptr)
	{
		m_camera->Update(dt);
		m_camera->SetTarget(t->m_position);
		m_camera->SetYaw(t->m_yaw);
	}
}