#include "Player.h"

Player::Player()
{
	m_model.makeModel("cube");
}

Player::~Player()
{

}

void Player::Update()
{

}

void Player::Render(Camera & cam)
{
	m_model.Draw(cam);
}
