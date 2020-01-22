#include "MapObject.h"



MapObject::MapObject()
{
}
//need to use enum for type will do it later

MapObject::MapObject(float x, float y, float width, float height, float rotation, string type,glm::vec3 scale,bool isCollidable)
{
	//set Vairables
	m_position = glm::vec3(x + (width / 2), 0, y + (height / 2));
	m_width = width;
	m_height = height;
	m_halfWidth = width / 2;
	m_halfHeight = height / 2;
	m_rotation = rotation;
	m_type = type;
	//set model
	m_isCollidable = isCollidable;
	m_model = Model(type,m_position,scale,rotation);
	//set bounds
	m_boundPoints.push_back(new glm::vec2(-m_halfWidth, m_halfHeight));
	m_boundPoints.push_back(new glm::vec2(m_halfWidth, m_halfHeight));
	m_boundPoints.push_back(new glm::vec2(m_halfWidth, -m_halfHeight));
	m_boundPoints.push_back(new glm::vec2(-m_halfWidth, -m_halfHeight));
	m_bounds = Polygon(m_boundPoints, m_position);
}


MapObject::~MapObject()
{

}

void MapObject::Update(float dt)
{

}

void MapObject::Draw(Camera* cam, Shader shader)
{
	m_model.Draw(cam, shader);
	m_bounds.Draw(cam);
}

Polygon MapObject::GetBounds()
{
	return m_bounds;
}

glm::vec3 MapObject::GetPosition()
{
	return m_position;
}
