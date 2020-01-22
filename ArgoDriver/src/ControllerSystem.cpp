#include "ControllerSystem.h"


ControllerSystem::ControllerSystem()
{
	m_fsm = FSMachine();
	m_inputManager = InputManager::GetInstance();
	BindKeys();
	SDL_Init(SDL_INIT_JOYSTICK);
	dir = 0;
	accelDir = 0;
	gGameController = SDL_JoystickOpen(0);

	StickLeft = new StickLeftCommand();
	StickRight = new StickRightCommand();
	ThrottleUp = new ThrottleUpCommand();
	ThrottleDown = new ThrottleDownCommand();
	NeutralStick = new NeutralStickCommand();
	NeutralThrottle = new NeutralThrottleCommand();

}

ControllerSystem::~ControllerSystem()
{

}

void ControllerSystem::BindKeys()
{

}

void ControllerSystem::Pause()
{
	m_paused = !m_paused;
}
void ControllerSystem::Exit()
{
	m_exit = !m_exit;
}

void ControllerSystem::Turn(float dir)
{
	if (m_player != nullptr)
	{
		Transformable* t = (Transformable*)m_player->GetComponent("transformable");
		if (t != nullptr)
		{
			if (dir > 1.25f)
			{
				dir = 1.25f;
			}
			if (dir < -1.25f)
			{
				dir = -1.25f;
			}
			t->m_yaw -= (dir*dts)* 2;
			if (dir > 0)
			{
				m_fsm.bankRight(t, dts);
			}
			else if (dir < 0)
			{
				m_fsm.bankLeft(t, dts);
			}
		}
	}
}

void ControllerSystem::GamepadControls()
{
	Turn(m_inputManager->GetLeftStickVectorNormal().x);

	Accelerate(GetAccelValue());
	Decelerate(GetDecelValue());
}

float ControllerSystem::GetAccelValue()
{
	float accel = m_inputManager->GetRightTrigger();
	accel = accel / 35000;
	if (accel <= 0)
	{
		accel = 0;
	}
	return accel;
}

float ControllerSystem::GetDecelValue()
{
	float decel = m_inputManager->GetLeftTrigger();
	decel = decel / 35000;
	if (decel < 0)
	{
		decel = 0;
	}
	return decel;
}

void ControllerSystem::Accelerate(float value)
{
	if (m_player != nullptr)
	{
		Transformable* t = (Transformable*)m_player->GetComponent("transformable");
		Velocity* v = (Velocity*)m_player->GetComponent("velocity");
		if (t != nullptr && v != nullptr)
		{
			if (v->m_acceleration < v->m_maxAcceleration)
			{
				if (value > 0)
				{
					v->m_acceleration += (value*dts);
					m_fsm.pitchForward(t, dts);
				}
			}
		}
	}
}

bool ControllerSystem::GetPaused()
{
	return m_paused;
}
bool ControllerSystem::GetExit()
{
	return m_exit;
}

void ControllerSystem::Decelerate(float value)
{
	if (m_player != nullptr)
	{
		Transformable* t = (Transformable*)m_player->GetComponent("transformable");
		Velocity* v = (Velocity*)m_player->GetComponent("velocity");
		if (t != nullptr && v != nullptr)
		{
			if (v->m_acceleration > (-v->m_maxAcceleration / 5))
			{
				if (value > 0)
				{
					v->m_acceleration -= (value*dts) * 2;
					m_fsm.pitchBackward(t, dts);
				}
			}
		}
	}
}

void ControllerSystem::HandleInput(float dt)
{

	Transformable* t = (Transformable*)m_player->GetComponent("transformable");

	if (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_JOYAXISMOTION)
		{
			if (e.jaxis.axis == 0)
			{
				if (e.jaxis.value < -JOYSTICK_DEADZONE)
				{
					StickLeft->execute(m_player, e.jaxis.value, dt);
				}
				else if (e.jaxis.value > JOYSTICK_DEADZONE)
				{
					StickRight->execute(m_player, e.jaxis.value, dt);
				}
				else
				{
					NeutralStick->execute(m_player, e.jaxis.value, dt);
				}
			}
			else if (e.jaxis.axis == 1)
			{
				if (e.jaxis.value < -JOYSTICK_DEADZONE)
				{
					ThrottleUp->execute(m_player, e.jaxis.value, dt);
				}
				else if (e.jaxis.value > JOYSTICK_DEADZONE)
				{
					ThrottleDown->execute(m_player, e.jaxis.value, dt);
				}
				else
				{
					NeutralThrottle->execute(m_player, e.jaxis.value, dt);
				}
			}
			if (e.jaxis.axis == 2)
			{
				if (e.jaxis.value < -JOYSTICK_DEADZONE)
				{
					ThrottleUp->execute(m_player, e.jaxis.value, dt);
				}
				else if (e.jaxis.value > JOYSTICK_DEADZONE)
				{
					ThrottleDown->execute(m_player, e.jaxis.value, dt);
				}
				else
				{
					NeutralThrottle->execute(m_player, e.jaxis.value, dt);
				}
			}
		}
	}
	dts = dt;
	if (m_player->accelValue > 0)
	{
		Accelerate(m_player->accelValue);
	}
	else if (m_player->accelValue < 0)
	{
		Decelerate(-(m_player->accelValue));
	}
	Turn(m_player->turnValue);

	m_inputManager->ProcessInput();
	m_inputManager->ConstantInput();

	if (m_inputManager->IsControllerConnected() == true)
	{
		GamepadControls();
	}
}

void ControllerSystem::SetEntity(Entity* e)
{
	m_player = e;
}

