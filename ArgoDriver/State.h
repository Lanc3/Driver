#pragma once

#include "FSMachine.h"
#include "Components.h"
#include <iostream>

using namespace std;
class FSMachine;
class State
{
public:
	virtual void idle(FSMachine* a)
	{
		cout << "State::Idling" << endl;
	}

	virtual void BankRight(Transformable* t, float dt)
	{
		cout << "State::Bank Right" << endl;
	}
	virtual void BankLeft(Transformable* t, float dt)
	{
		cout << "State::Bank Left" << endl;
	}
	virtual void PitchForward(Transformable* t, float dt)
	{
		cout << "State::Pitch Forward" << endl;
	}
	virtual void PitchBackward(Transformable* t, float dt)
	{
		cout << "State::Pitch Backward" << endl;
	}
};