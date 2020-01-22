//#include "stdafx.h"
#include "State.h"
#include "IdleState.h"
#include "FSMachine.h"

FSMachine::FSMachine()
{
	current = new IdleState();
}

void FSMachine::idle()
{
	current->idle(this);
}

void FSMachine::bankLeft(Transformable* t, float dt)
{
	current->BankLeft(t, dt);
}

void FSMachine::bankRight(Transformable* t, float dt)
{
	current->BankRight(t, dt);
}

void FSMachine::pitchForward(Transformable* t, float dt)
{
	current->PitchForward(t, dt);
}

void FSMachine::pitchBackward(Transformable* t, float dt)
{
	current->PitchBackward(t, dt);
}