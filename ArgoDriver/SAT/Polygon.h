#pragma once

#include "Collider.h"
#include "Camera.h"
#include "Line.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Polygon : public Collider
{

private:
	float posX;
	float posY;
	glm::vec2 center;
	Line l;
	bool renderoutLines = true;
public:
	Polygon();
	/*
	Takes a sdl_point points of the shape. 
	amount of points in shape.
	*/
	Polygon(SDL_Point* _points, int _size);

	Polygon(SDL_Point* _points, int _size, glm::vec3 startingPosition);
	Polygon(vector<glm::vec2*> _points, glm::vec3 startingPosition);
	/*
	Move the collider relative to the current postion. e.g. x += value, y+= value
	*/
	void move(float x, float y);
	void move(glm::vec2 moveAmount);
	/*
	Set the overall position of the collider. e.g x = value, y = value
	*/
	void SetPosition(float x, float y);

	void SetPosition(glm::vec3 _position);
	/*
	Calls a draw fucntion to draw the shape of the poly in 3D
	*/
	void Draw(Camera *cam);

	void Update(float dt);

	void CalculateCenter();

	glm::vec2 GetCenter();
};
