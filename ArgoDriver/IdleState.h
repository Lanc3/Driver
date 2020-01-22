#pragma once

#include "FSMachine.h"
#include "State.h"

class IdleState : public State
{
public:
	IdleState() { };
	~IdleState() { };

	void BankRight(Transformable * t, float dt);

	void BankLeft(Transformable* a, float dt);
	void PitchForward(Transformable * t, float dt);
	void PitchBackward(Transformable * t, float dt);
	float lerp(float t, float a, float b);
	float SinusoidalInOut(float dt, float start, float change, float time);
	float SinusoidalIn(float dt, float start, float change);
	float SinusoidalOut(float dt, float start, float change);
};