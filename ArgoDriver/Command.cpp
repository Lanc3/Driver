
#include "Command.h"

#include <iostream>


void StickRightCommand::stickRight(Entity* e, float value, float dt)
{
	float val = (value * dt)/2000;
	e->turnValue += val;
	std::cout << "right" << std::endl;
}

void ThrottleUpCommand::throttleUp(Entity* e, float value, float dt)
{
	float val = (value * dt)/2000;
	e->accelValue -= val;
	std::cout << "up" << std::endl;
}

void ThrottleDownCommand::throttleDown(Entity* e, float value, float dt)
{
	float val = (value * dt)/2000;
	e->accelValue -= val;
	std::cout << "down" << std::endl;
}

void StickLeftCommand::stickLeft(Entity* e, float value, float dt)
{
	float val = (value * dt)/2000;
	e->turnValue += val;
	std::cout << "left" << std::endl;
}

void NeutralStickCommand::neutralStick(Entity * e, float value, float dt)
{
	e->turnValue = 0;
}

void NeutralThrottleCommand::neutralThrottle(Entity * e, float value, float dt)
{
	e->accelValue = 0;
}
