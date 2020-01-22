#include "AIMovementSystem.h"

AIMovementSystem::AIMovementSystem(vector<glm::vec3>_points, vector<glm::vec3>_civPointsOne, vector<glm::vec3>_civPointsTwo)
{
	listOfPoints = _points;
	listOfCivOnePoints = _civPointsOne;
	listOfCivTwoPoints = _civPointsTwo;
}

AIMovementSystem::AIMovementSystem()
{
}

AIMovementSystem::~AIMovementSystem()
{

}

void AIMovementSystem::Update(float dt)
{
	for (Entity* e : m_entities)
	{
		Transformable* t = (Transformable*)e->GetComponent("transformable");
		Velocity * v = (Velocity*)e->GetComponent("velocity");
		AISteering * st = (AISteering*)e->GetComponent("AISteering");
		IDTag * ID = (IDTag*)e->GetComponent("IDTag");
		if (v != nullptr && t != nullptr && ID->m_name == "enemy")
		{
			float deltaX;
			float deltaZ;
			st->m_steering = glm::normalize(glm::vec3(listOfPoints.at(checkpointIndex).x - t->m_position.x, 0, listOfPoints.at(checkpointIndex).z - t->m_position.z));

			glm::vec3 cross = glm::cross(t->m_direction, st->m_steering);
			t->m_direction = glm::rotate(t->m_direction, glm::radians(turnSpeed)*dt, cross);
			t->m_yaw = atan2(-t->m_direction.z, t->m_direction.x);
			//
			//AIstuff
			t->m_dynamicLength = glm::length(v->m_velocity) / v->m_maxAcceleration;
			t->m_ahead = t->m_position + (v->m_velocity * 50.f);
			t->m_ahead2 = t->m_position + (v->m_velocity * (50.f* 0.5f));


			Entity* mostThreatening = findMostThreateningObstacle();

			m_avoidance = glm::vec3(0);

			if (mostThreatening != nullptr) {
				CircleBounds * cB = (CircleBounds*)mostThreatening->GetComponent("circleBounds");
				m_avoidance.x = t->m_ahead.x - cB->m_bounds->GetCenter().x;
				m_avoidance.z = t->m_ahead.z - cB->m_bounds->GetCenter().z;

				glm::normalize(m_avoidance);
				m_avoidance = m_avoidance * 3.0f;
			}
			else {
				m_avoidance = glm::vec3(0);

			}
			v->m_velocity = t->m_direction * (v->m_acceleration * 0.01f);

			deltaX = t->m_position.x - listOfPoints.at(checkpointIndex).x;
			deltaZ = t->m_position.z - listOfPoints.at(checkpointIndex).z;

			futureAngle = abs(glm::degrees(atan2(deltaZ, -deltaX)));

			deltaX = t->m_position.x - listOfPoints.at(checkpointIndexSecond).x;
			deltaZ = t->m_position.z - listOfPoints.at(checkpointIndexSecond).z;

			futureAngleTwo = abs(glm::degrees(atan2(deltaZ, -deltaX)));

			float total = abs(futureAngle - futureAngleTwo);

			if (total > 20)
			{
				if (v->m_acceleration > 2.0f)
				{
					v->m_acceleration -= 0.05f;
				}
			}
			else
			{
				if (v->m_acceleration < 5.f)
				{
					v->m_acceleration += 0.05f;
				}
			}

			if (v->m_acceleration <= 2)
			{
				turnSpeed = 120;
			}
			else if (v->m_acceleration >= 4)
			{
				turnSpeed = 60;
			}
			else
			{
				turnSpeed = 90;
			}

			float distance = glm::distance(t->m_position, listOfPoints.at(checkpointIndex));
			if (distance < 5)
			{
				checkpointIndex++;
				checkpointIndexSecond++;
			}
			if (checkpointIndexSecond == listOfPoints.size() - 1)
			{
				checkpointIndexSecond = 0;
			}
			if (checkpointIndex == listOfPoints.size() - 1)
			{
				lapCount++;
				checkpointIndex = 0;
			}

		}


		if (v != nullptr && t != nullptr && ID->m_name == "civOne")
		{
			float deltaX;
			float deltaZ;
			st->m_steering = glm::vec3(0);
			st->m_steering = glm::normalize(glm::vec3(listOfCivOnePoints.at(civOnePointIndex).x - t->m_position.x, 0, listOfCivOnePoints.at(civOnePointIndex).z - t->m_position.z));

			glm::vec3 cross = glm::cross(t->m_direction, st->m_steering);
			t->m_direction = glm::rotate(t->m_direction, glm::radians(turnSpeed)*dt, cross);
			t->m_yaw = atan2(-t->m_direction.z, t->m_direction.x) + glm::radians(180.f);
			//
			//AIstuff
			t->m_dynamicLength = glm::length(v->m_velocity) / v->m_maxAcceleration;
			t->m_ahead = t->m_position + (v->m_velocity * 50.f);
			t->m_ahead2 = t->m_position + (v->m_velocity * (50.f* 0.5f));


			Entity* mostThreatening = findMostThreateningObstacle();

			m_avoidance = glm::vec3(0);

			if (mostThreatening != nullptr) {
				CircleBounds * cB = (CircleBounds*)mostThreatening->GetComponent("circleBounds");
				m_avoidance.x = t->m_ahead.x - cB->m_bounds->GetCenter().x;
				m_avoidance.z = t->m_ahead.z - cB->m_bounds->GetCenter().z;

				glm::normalize(m_avoidance);
				m_avoidance = m_avoidance * 3.0f;
			}
			else {
				m_avoidance = glm::vec3(0);

			}
			v->m_velocity = t->m_direction * (v->m_acceleration * 0.01f);
			//t->m_position += v->m_velocity;
			deltaX = t->m_position.x - listOfCivOnePoints.at(civOnePointIndex).x;
			deltaZ = t->m_position.z - listOfCivOnePoints.at(civOnePointIndex).z;

			futureAngle = abs(glm::degrees(atan2(deltaZ, -deltaX)));

			deltaX = t->m_position.x - listOfCivOnePoints.at(civOnePointIndexSecond).x;
			deltaZ = t->m_position.z - listOfCivOnePoints.at(civOnePointIndexSecond).z;

			futureAngleTwo = abs(glm::degrees(atan2(deltaZ, -deltaX)));

			float total = abs(futureAngle - futureAngleTwo);

			if (total > 20)
			{
				if (v->m_acceleration > 2.0f)
				{
					v->m_acceleration -= 0.05f;
				}
			}
			else
			{
				if (v->m_acceleration < 5.f)
				{
					v->m_acceleration += 0.05f;
				}
			}

			if (v->m_acceleration <= 2)
			{
				turnSpeed = 120;
			}
			else if (v->m_acceleration >= 4)
			{
				turnSpeed = 60;
			}
			else
			{
				turnSpeed = 90;
			}

			float distance = glm::distance(t->m_position, listOfCivOnePoints.at(civOnePointIndex));
			if (distance < 5)
			{
				civOnePointIndex++;
				civOnePointIndexSecond++;
			}
			if (civOnePointIndexSecond == listOfCivOnePoints.size() - 1)
			{
				civOnePointIndexSecond = 0;
			}
			if (civOnePointIndex == listOfCivOnePoints.size() - 1)
			{
				lapCount++;
				civOnePointIndex = 0;
			}

		}

		if (v != nullptr && t != nullptr && ID->m_name == "civTwo")
		{
			float deltaX;
			float deltaZ;
			st->m_steering = glm::normalize(glm::vec3(listOfCivTwoPoints.at(civTwoPointIndex).x - t->m_position.x, 0, listOfCivTwoPoints.at(civTwoPointIndex).z - t->m_position.z));

			glm::vec3 cross = glm::cross(t->m_direction, st->m_steering);
			t->m_direction = glm::rotate(t->m_direction, glm::radians(turnSpeed)*dt, cross);
			t->m_yaw = atan2(-t->m_direction.z, t->m_direction.x) + glm::radians(180.f);
			//
			//AIstuff
			t->m_dynamicLength = glm::length(v->m_velocity) / v->m_maxAcceleration;
			t->m_ahead = t->m_position + (v->m_velocity * 50.f);
			t->m_ahead2 = t->m_position + (v->m_velocity * (50.f* 0.5f));
			t->m_position += v->m_velocity *dt;

			Entity* mostThreatening = findMostThreateningObstacle();

			m_avoidance = glm::vec3(0);

			if (mostThreatening != nullptr) {
				CircleBounds * cB = (CircleBounds*)mostThreatening->GetComponent("circleBounds");
				m_avoidance.x = t->m_ahead.x - cB->m_bounds->GetCenter().x;
				m_avoidance.z = t->m_ahead.z - cB->m_bounds->GetCenter().z;

				glm::normalize(m_avoidance);
				m_avoidance = m_avoidance * 3.0f;
			}
			else {
				m_avoidance = glm::vec3(0);

			}
			v->m_velocity = t->m_direction * (v->m_acceleration * 0.01f);

			deltaX = t->m_position.x - listOfCivTwoPoints.at(civTwoPointIndex).x;
			deltaZ = t->m_position.z - listOfCivTwoPoints.at(civTwoPointIndex).z;

			futureAngle = abs(glm::degrees(atan2(deltaZ, -deltaX)));

			deltaX = t->m_position.x - listOfCivTwoPoints.at(civTwoPointIndexSecond).x;
			deltaZ = t->m_position.z - listOfCivTwoPoints.at(civTwoPointIndexSecond).z;

			futureAngleTwo = abs(glm::degrees(atan2(deltaZ, -deltaX)));

			float total = abs(futureAngle - futureAngleTwo);

			if (total > 20)
			{
				if (v->m_acceleration > 2.0f)
				{
					v->m_acceleration -= 0.05f;
				}
			}
			else
			{
				if (v->m_acceleration < 5.f)
				{
					v->m_acceleration += 0.05f;
				}
			}

			if (v->m_acceleration <= 2)
			{
				turnSpeed = 120;
			}
			else if (v->m_acceleration >= 4)
			{
				turnSpeed = 60;
			}
			else
			{
				turnSpeed = 90;
			}

			float distance = glm::distance(t->m_position, listOfCivTwoPoints.at(civTwoPointIndex));
			if (distance < 5)
			{
				civTwoPointIndex++;
				civTwoPointIndexSecond++;
			}
			if (civTwoPointIndexSecond == listOfCivTwoPoints.size() - 1)
			{
				civTwoPointIndexSecond = 0;
			}
			if (civTwoPointIndex == listOfCivTwoPoints.size() - 1)
			{
				lapCount++;
				civTwoPointIndex = 0;
			}

		}
	}
}

void AIMovementSystem::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);
}

void AIMovementSystem::AddObjectToAvoid(Entity * entity)
{
	m_listOfAvoidanceObjects.push_back(entity);
}
Entity * AIMovementSystem::findMostThreateningObstacle() {
	Entity * mostThreatening = nullptr;
	Transformable* otherPos = nullptr;
	for (int i = 0; i < m_listOfAvoidanceObjects.size(); i++) {
		Entity * obstacle = m_listOfAvoidanceObjects[i];
		for (Entity* e : m_entities)
		{
			Transformable* AI_t = (Transformable*)e->GetComponent("transformable");
			Transformable* Player_t = (Transformable*)obstacle->GetComponent("transformable");
			CircleBounds * Player_Bounds = (CircleBounds*)obstacle->GetComponent("circleBounds");
			//bool collision = Player_Bounds->m_bounds->LineIntersectsCircle(AI_t->m_ahead, AI_t->m_ahead2);

			//// "position" is the character's current position
			//if (Player_Bounds->m_bounds->LineIntersectsCircle(AI_t->m_ahead, AI_t->m_ahead2))
			//{
			//	cout << "hit" << endl;
			//	mostThreatening = obstacle;
			//}

		}

	}

	return mostThreatening;
}