#include "Entity.h"

Entity::Entity() 
{

}

Entity::Entity(std::string name) 
{
	m_name = name;
}

void Entity::AddComponent(Component* c) 
{
	m_components[c->GetName()] = c;
}

void Entity::RemoveComponent(Component* c) 
{
	m_components.erase(c->GetName());
}

Component* Entity::GetComponent(std::string name) 
{
	std::map<std::string, Component*>::iterator it;
	it = m_components.find(name);

	if (it != m_components.end())
		return it->second;
		//std::cout << "No component of " << name << " found!" << std::endl;

	return nullptr;
}

std::string Entity::GetName() 
{
	return m_name;
}

void Entity::SetAlive(bool value)
{
	m_alive = value;
}

bool Entity::GetAlive() const
{
	return m_alive;
}