#include "Polygon.h"

Polygon::Polygon() {};

Polygon::Polygon(SDL_Point* _points, int _size)
{
	posX = (float)_points[0].x;
	posY = (float)_points[0].y;
	size = _size;
	points = new glm::vec2[size];
	for (int i = 0; i < _size; i++)
	{
		points[i].x = _points[i].x;
		points[i].y = _points[i].y;
	}
}

Polygon::Polygon(SDL_Point* _points,int _size, glm::vec3 startingPosition)
{
	posX = startingPosition.x;
	posY = startingPosition.z;
	points = new glm::vec2[size];
	for (int i = 0; i < _size; i++)
	{
		points[i].x = _points[i].y;
		points[i].y = _points[i].y;
	}
}

Polygon::Polygon(vector<glm::vec2*> _points, glm::vec3 startingPosition)
{
	posX = startingPosition.x;
	posY = startingPosition.z;
	size = _points.size();
	points = new glm::vec2[size];
	for (int i = 0; i < _points.size() ; i++)
	{
		points[i].x = posX + (float)_points[i]->x;
		points[i].y = posY + (float)_points[i]->y;
	}
}


void Polygon::move(float x, float y)
{
	for (int i = 0; i < size; i++)
	{
		points[i].x += x;
		points[i].y += y;
	}
}

void Polygon::move(glm::vec2 moveAmount)
{
	for (int i = 0; i < size; i++)
	{
		points[i].x += moveAmount.x;
		points[i].y += moveAmount.y;
	}
}

void Polygon::SetPosition(float x, float y)
{
	for (int i = 0; i < size; i++)
	{
		float offsetX = posX - x;
		float offsetY = posY - y;
		points[i].x -= offsetX;
		points[i].y -= offsetY;
	}
	posX = x;
	posY = y;
}

void Polygon::SetPosition(glm::vec3 _position)
{
	for (int i = 0; i < size; i++)
	{
		float offsetX = posX - _position.x;
		float offsetY = posY - _position.z;
		points[i].x -= offsetX;
		points[i].y -= offsetY;
	}
	posX = _position.x;
	posY = _position.z;
}

void Polygon::Draw(Camera * cam)
{
	for (int i = 0; i < size; i++)
	{
		if (i != size - 1)
		{
			//l = Line(glm::vec3(points[i].x, 0, points[i].y), glm::vec3(points[i + 1].x, 0, points[i + 1].y));
			//l.Draw(cam);
		}
		else
		{
			//l = Line(glm::vec3(points[i].x, 0, points[i].y), glm::vec3(points[0].x, 0, points[0].y));
			//l.Draw(cam);
		}
	}
}

void Polygon::Update(float dt)
{
	/*for (int i = 0; i < size; i++)
	{
		points[i].x += posX;
		points[i].y += posY;
	}*/
}

void Polygon::CalculateCenter()
{
	glm::vec2 point = glm::vec2(0, 0);
	if (size != 0)
	{
		for (int i = 0; i < size; i++)
		{
			point.x = (points[i].x / size);
			point.y = (points[i].y / size);
		}
	}
	center = point;
}

glm::vec2 Polygon::GetCenter()
{
	return glm::vec2(posX,posY);
}
