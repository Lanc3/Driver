#pragma once

#include "Entity.h"
#include "Components.h"
#include "FSMachine.h"
#include "Command.h"

#include <vector>
#include "FLInputManager.h"

class ControllerSystem : public EventListener {
public:
	ControllerSystem();
	~ControllerSystem();

	void Pause();
	void Exit();

	void GamepadControls();
	float GetAccelValue();
	float GetDecelValue();

	void Accelerate(float value);
	void Decelerate(float value);
	void Turn(float dir);

	bool GetPaused();
	bool GetExit();

	void HandleInput(float dt);
	void SetEntity(Entity* e);


private:
	void BindKeys();

	int JOYSTICK_DEADZONE = 8000;
	bool m_paused;
	bool m_exit;
	float dir;
	float accelDir;

	SDL_Event e;
	SDL_Joystick* gGameController = NULL;
	FSMachine m_fsm;
	InputManager* m_inputManager;
	//InputM

	CommandC* StickLeft;
	CommandC* StickRight;
	CommandC* ThrottleUp;
	CommandC* ThrottleDown;
	CommandC* NeutralStick;
	CommandC* NeutralThrottle;

	Transformable* t;

	Entity* m_player;
	float dts;

};