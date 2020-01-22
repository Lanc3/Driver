#include "Collider.h"

Collider::Collider() {};

Collider::~Collider() {};

int Collider::getSize()
{
	return size;
}

glm::vec2* Collider::getPoints()
{
	return points;
}


