#pragma once

#include <vector>
#include <iostream>
#include "Components.h"
#include "Entity.h"
#include "FSMachine.h"

class CommandC
{
public:

	virtual ~CommandC() { }

	float* accelValue = 0;
	float* turnValue = 0;

	virtual void execute(Entity* e, float value, float dt) = 0;
	FSMachine machine;
	
protected:
	CommandC () {}
};

class StickLeftCommand : public CommandC
{
public:
	virtual void execute(Entity* e, float value, float dt) { stickLeft(e, value, dt); }

	void stickLeft(Entity * e, float value, float dt);
};

class StickRightCommand : public CommandC
{
public:
	virtual void execute(Entity* e, float value, float dt) { stickRight(e, value, dt); }

	void stickRight(Entity * e, float value, float dt);
};

class ThrottleUpCommand : public CommandC
{
public:
	virtual void execute(Entity* e, float value, float dt) { throttleUp(e, value, dt); }

	void throttleUp(Entity * e, float value, float dt);
};

class ThrottleDownCommand : public CommandC
{
public:
	virtual void execute(Entity* e, float value, float dt) { throttleDown(e, value, dt); }

	void throttleDown(Entity * e, float value, float dt);
};

class NeutralStickCommand : public CommandC
{
public:
	virtual void execute(Entity* e, float value, float dt) { neutralStick(e, value, dt); }

	void neutralStick(Entity * e, float value, float dt);
};

class NeutralThrottleCommand : public CommandC
{
public:
	virtual void execute(Entity* e, float value, float dt) { neutralThrottle(e, value, dt); }

	void neutralThrottle(Entity * e, float value, float dt);
};
