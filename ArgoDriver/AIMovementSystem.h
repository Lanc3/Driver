#pragma once

#include "Components.h"
#include "Entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>
#define PI 3.14159265359
class AIMovementSystem {
public:
	AIMovementSystem(vector<glm::vec3>_points,vector<glm::vec3>_civPointsOne, vector<glm::vec3>_civPointsTwo);
	AIMovementSystem();
	~AIMovementSystem();

	void Update(float dt);
	void AddEntity(Entity* entity);
	void AddObjectToAvoid(Entity * entity);

	Entity * findMostThreateningObstacle();

private:
	std::vector<Entity*> m_entities;
	vector<glm::vec3> listOfPoints;
	vector<glm::vec3> listOfCivOnePoints;
	vector<glm::vec3> listOfCivTwoPoints;
	int checkpointIndex = 0, checkpointIndexSecond = 1;
	int civOnePointIndex = 0, civOnePointIndexSecond = 1;
	int civTwoPointIndex = 0, civTwoPointIndexSecond = 1;
	int lapCount = 0;
	vector<Entity*> m_listOfAvoidanceObjects;
	glm::vec3 m_avoidance;
	glm::vec3 futurePointOne, futurePointTwo;
	float futureAngle,futureAngleTwo,turnSpeed = 60.0f;
};