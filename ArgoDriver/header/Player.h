#pragma once

#include "Entity.h"
#include "Camera.h"
#include "Model.h"

class Player : public Entity {
public:
	Player();
	~Player();

	void Update(float dt);
	void Render(Shader shader, Camera & cam, int SCREENWIDTH, int SCREENHEIGHT);
	void ProcessInput(float dt);

	glm::vec3 GetPosition();
	GLfloat Getdx();
	GLfloat Getdz();
	GLfloat GetYaw();
	void SetPosition(glm::vec3 pos);
private:
	Model m_model;

	GLfloat m_speed;
	GLfloat m_rotateSpeed;
	GLfloat m_velocity;
	GLfloat m_acceleration;
	GLfloat m_maxVelocity;
	GLfloat m_yaw;

	glm::vec3 m_upAxis;
	glm::vec3 m_rightAxis;
	glm::vec3 m_worldUp;

	GLfloat dx;
	GLfloat dz;

	glm::vec3 m_position;
	glm::vec3 m_front;
};