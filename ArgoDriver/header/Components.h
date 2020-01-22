#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Component.h"
#include "Model.h"

#include "SAT\Polygon.h"
#include "Circle.h"


class Transformable : public Component {
public:
	glm::vec3 m_position = glm::vec3(0, 0, 0);
	glm::vec3 m_oldDirection = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_ahead, m_ahead2;
	float MAX_SEE_AHEAD = 10;
	float m_dynamicLength;
	GLfloat m_yaw = 0;
	GLfloat m_pitch = 0;
	GLfloat m_roll = 0;
	GLfloat m_bank = 0;

	GLfloat angle = 0;

	GLfloat dx = 0;
	GLfloat dy = 0;
	GLfloat dz = 0;

	Transformable() : Component("transformable") {}
	Transformable(glm::vec3 position, GLfloat yaw, GLfloat pitch, GLfloat roll) : Component("transformable")
	{
		m_position = position;
		m_yaw = yaw;
		m_pitch = pitch;
		m_roll = roll;
	}
};

class Velocity : public Component {
public:
	GLfloat m_rotateSpeed = 0;
	
	GLfloat m_maxAcceleration = 0;
	GLfloat m_acceleration = 0;
	GLfloat m_speed = 0;

	glm::vec3 m_velocity = glm::vec3(0);

	Velocity() : Component("velocity") {}
	Velocity(GLfloat speed, GLfloat rotateSpeed, GLfloat maxAccel) : Component("velocity")
	{
		m_speed = speed;
		m_rotateSpeed = rotateSpeed;
		m_maxAcceleration = maxAccel;
	}
};

class ModelMesh : public Component {
public:
	Model m_model;

	ModelMesh() : Component("modelMesh")
	{ 
		
	}
	ModelMesh(std::string modelID, glm::vec3 startingPosition,glm::vec3 scale,float rotation) : Component("modelMesh")
	{ 
		m_model = Model(modelID,startingPosition,scale,rotation); 
	}	
};

class PolygonBounds : public Component {
public:
	Polygon * m_bounds;
	PolygonBounds() : Component("polygonBounds")
	{

	}
	PolygonBounds(vector<glm::vec2*> _points, glm::vec3 startingPosition) : Component("polygonBounds")
	{
		m_bounds = new Polygon(_points, startingPosition);
	}
};

class CircleBounds : public Component {
public:
	Circle * m_bounds;
	CircleBounds() : Component("circleBounds")
	{

	}
	CircleBounds( glm::vec3 startingPosition,float radius) : Component("circleBounds")
	{
		m_bounds = new Circle( startingPosition,radius);
	}
};

class AISteering : public Component {
public:
	glm::vec3 m_steering;

	AISteering() : Component("AISteering")
	{

	}
};
class IDTag : public Component {
public:
	string m_name;

	IDTag(string name) : Component("IDTag")
	{
		m_name = name;
	}
};

class Controllable : public Component {
public:
	Controllable() : Component("controllable") {}
};

class Collidable : public Component {
public:
	bool m_collidable;
	float m_radius;

	Collidable() : Component("collidable") {}
	Collidable(float r) : Component("collidable")
	{
		m_collidable = true;
		m_radius = r;
	}
};

class Explosive : public Component {
public:
	float m_radius;
	glm::vec3 m_force;

	Explosive() : Component("explosive") {}
	Explosive(float radius, glm::vec3 force) : Component("explosive")
	{
		m_radius = radius;
		m_force = force;
	}
};

class Shield : public Component {
public:
	float m_duration;

	Shield() : Component("shield") {}
	Shield(float time) : Component("shield")
	{
		m_duration = time;
	}
};

class Boost : public Component {
public:
	float m_duration;
	glm::vec3 m_force;

	Boost() : Component("boost") {}
	Boost(float time, glm::vec3 force) : Component("boost")
	{
		m_duration = time;
		m_force = force;
	}
};

class ParticleEffect : public Component {
public:
	string m_type;

	ParticleEffect() : Component("particleeffect") {}
	ParticleEffect(string effectName) : Component("particle_effect")
	{
		m_type = effectName;
	}
};

class SeekingTarget : public Component {
public:
	glm::vec3 m_targetPos;

	SeekingTarget() : Component("seekingtarget") {}
	SeekingTarget(glm::vec3 targetPosition) : Component("seekingtarget")
	{
		m_targetPos = targetPosition;
	}
};

class LightSource : public Component {
public:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_radius;
	aiColor3D m_colour;

	LightSource() : Component("lightSource")
	{

	}
	LightSource(glm::vec3 position, glm::vec3 direction, float radius, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, aiColor3D colour)
		: Component("lightSource")
	{
		if (position != glm::vec3(0))
		{
			m_position = position;
			m_radius = radius;
		}
		else
		{
			m_direction = direction;
		}

		m_ambient = ambient;
		m_diffuse = diffuse;
		m_specular = specular;
		m_colour = colour;
	}
};