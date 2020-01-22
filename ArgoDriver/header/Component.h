#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component {
public:
	Component() {};
	Component(std::string name) { m_name = name; }
	std::string GetName() { return m_name; }
protected:
	std::string m_name;
};

#endif