#include "Player.h"

Player::Player()
{
	m_model.MakeModel("nanosuit");
	m_acceleration = 2.f;
	m_maxVelocity = 50.f;
	m_yaw = 0;
	m_position = glm::vec3(0, 0, 0);
	m_model.Translate(m_position);

	m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_rightAxis = glm::vec3(1.f, 0.0f, 0.0f);
	m_worldUp = glm::vec3(0.0f, 1.f, 0.0f);

	dx = 0;
	dz = 0;

	m_speed = 0.1f;
	m_rotateSpeed = 1.f;
}

Player::~Player()
{

}

void Player::Update(float dt)
{
	m_front = glm::normalize(glm::vec3(cos(glm::radians(m_yaw)), 0, sin(glm::radians(m_yaw))));

	m_position = m_front * dz;
	std::cout << "Player Pos: " << m_position.x << "," << m_position.y << "," << m_position.z << std::endl;
	m_model.Translate(glm::vec3(0, 0, dz));
}

void Player::Render(Shader shader, Camera & cam, int SCREENWIDTH, int SCREENHEIGHT)
{
	m_model.Draw(shader, cam, SCREENWIDTH, SCREENHEIGHT);
} 

void Player::ProcessInput(float dt)
{
	SDL_PumpEvents();
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_W])
	{
		dz += m_speed * dt;
	}

	if (keystate[SDL_SCANCODE_D])
	{
		m_yaw -= m_rotateSpeed * dt;
		m_model.Rotate(-(m_rotateSpeed * dt));
	}
	else if (keystate[SDL_SCANCODE_A])
	{
		m_yaw += m_rotateSpeed * dt;
		m_model.Rotate(m_rotateSpeed * dt);
	}

}

void Player::SetPosition(glm::vec3 pos) { m_position = pos; }

glm::vec3 Player::GetPosition() {	return m_position;	}
GLfloat Player::Getdx() {	return dx;	}
GLfloat Player::Getdz() { return dz; }
GLfloat Player::GetYaw() {	return m_yaw;	}