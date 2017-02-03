#include "Scene.h"

using namespace std;


Scene::Scene(Scenes title) : m_title(title)
{
}

void Scene::enter()
{
	std::cout << " entered" << std::endl;
}

void Scene::exit()
{
}

void Scene::updateInput()
{

}

void Scene::cleanUpRecources()
{

}

const Scenes Scene::getTitle()
{
	return m_title;
}
