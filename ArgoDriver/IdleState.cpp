//#include "stdafx.h"
#include "IdleState.h"
#include <iostream>


using namespace std;


void IdleState::BankRight(Transformable* t, float dt)
{
	t->m_bank += SinusoidalInOut(dt, 0, -180, 2);
}

void IdleState::BankLeft(Transformable* t, float dt)
{
	t->m_bank += SinusoidalInOut(dt, 0, 180, 2);	
}

void IdleState::PitchForward(Transformable* t, float dt)
{
	t->m_pitch += SinusoidalInOut(dt, 0, 180, 5);
}

void IdleState::PitchBackward(Transformable* t, float dt)
{
	t->m_pitch += SinusoidalInOut(dt, 0, -180, 5);
}

float IdleState::lerp(float t, float a, float b)
{
	return (a + 45 * (b - a));
}
float IdleState::SinusoidalInOut(float dt, float start, float change, float time)
{
	return -change / 2 * (cos(PI*dt / time) - 1) + start;
}
float IdleState::SinusoidalIn(float dt, float start, float change)
{
	return -change * cos(dt / 2 * (PI / 2)) + change + start;
}
float IdleState::SinusoidalOut(float dt, float start, float change)
{
	return change * sin(dt / 2 * (PI / 2)) + start;
}