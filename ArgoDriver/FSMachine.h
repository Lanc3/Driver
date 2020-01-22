#pragma once
#include "State.h"
#include "Components.h"

class FSMachine
{
	class State* current;

public:
	FSMachine();
	void setCurrent(State* s)
	{
		current = s;
	}

	void idle();
	void bankLeft(Transformable * t, float dt);
	void bankRight(Transformable * t, float dt);
	void pitchForward(Transformable * t, float dt);
	void pitchBackward(Transformable * t, float dt);

};