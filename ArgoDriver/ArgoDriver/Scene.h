#pragma once
#include "SceneManager.h"
#include <GL\glew.h>

#include <iostream>
using namespace std;



class Scene
{
public:
	
	Scene(Scenes title);

	//called automatically when a scene becomes active, used in sceneMgr
	virtual void enter();

	//called automatically when a scene becomes inactive, used in sceneMgr
	virtual void exit();
	
	virtual void cleanUpRecources();
	//simple method that returns the title of the scene, used in sceneMgr
	const Scenes getTitle();

	virtual void update(float dt) = 0;
	virtual void updateInput(float dt, unsigned char key, GLfloat xoffset, GLfloat yoffset);
	virtual void draw() = 0;

protected:
	Scenes m_title;

};

