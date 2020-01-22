#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Model.h"
#include "Line.h"
#include "SAT\Polygon.h"
#include "Camera.h"

class MapObject
{
public:
	MapObject();
	MapObject(float x,float y,float width,float height, float rotation,string type,glm::vec3 scale,bool isCollidable);
	~MapObject();
	void Update(float dt);
	void Draw(Camera* cam, Shader shader);
	Polygon GetBounds();
	glm::vec3 GetPosition();
	bool m_isCollidable;
private:
	Polygon m_bounds;
	vector<glm::vec2*> m_boundPoints;
	glm::vec3 m_position;
	float m_width, m_height, m_rotation,m_halfWidth,m_halfHeight;
	string m_type;
	Model m_model;
};

