#ifndef COLLIDER_H
#define COLLIDER_H
#include "math.h"
#include "glm/glm.hpp"

class Collider
{
public:
	Collider();
	~Collider();

	glm::vec2* getPoints();
	int getSize();

protected:
	glm::vec2* points;
	int size;
};
#endif