#pragma once

#include "Component.h"

#include <string>
#include <map>
#include <vector>
#include <iostream>

class Entity {
public:
	Entity();
	Entity(std::string name);

	void AddComponent(Component* c);
	void RemoveComponent(Component* c);
	Component* GetComponent(std::string name);

	std::string GetName();

	void SetAlive(bool value);
	bool GetAlive() const;
	float accelValue;
	float turnValue;
	int id;
	bool playerSet = false;
private:
	
	std::string m_name;
	std::map<std::string, Component*> m_components;
	bool m_alive = true;
};
