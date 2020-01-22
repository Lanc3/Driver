#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <cmath>
#include "Polygon.h"

#include "PixelCollider.h"
#include <glm/glm.hpp>
#include <vector>

struct CollisionData {
	bool isColliding;
	bool willCollide;
	glm::vec2 MTV;
};

class CollisionManager 
{
private:
	bool checkRect(RectFloat* rect1, RectFloat* rect2);
	void checkConcave(std::vector<Collider*>* colliders, Collider* col);
	bool isLeft(glm::vec2 axis, glm::vec2 point);
	
public:
	CollisionManager();
	~CollisionManager();
	float IntervalDistance(float minA, float maxA, float minB, float maxB);
	bool SAT(Collider& col1, Collider& col2);
	CollisionData SATForConvex(Polygon & colA, Polygon & colB, glm::vec2 velocity);
	void ProjectPolygon(glm::vec2 axis, glm::vec2 * points, int size, float & min, float & max);
	bool PixelCollision(PixelCollider& col1, PixelCollider& col2);
};
#endif