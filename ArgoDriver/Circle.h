#pragma once
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Circle
{
public:
	Circle();
	Circle(glm::vec3 position, float radius);
	void SetCenter(glm::vec3 position);
	~Circle();
	float Distance(glm::vec3 objectA, glm::vec3 objectB);
	bool LineIntersectsCircle(glm::vec3 ahead2, glm::vec3 ahead);

	glm::vec3 GetCenter();
	float GetRadius();
private:
	glm::vec3 m_center;
	float m_radius;
};

