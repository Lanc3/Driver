#pragma once

#include "System.h"
#include "Components.h"
#include "Entity.h"
#include "Net.h"

class MultiplayerSystem : public System {
public:
	MultiplayerSystem();
	MultiplayerSystem(std::vector<Entity*> players);
	~MultiplayerSystem();

	void Update(float dt);
	void UpdatePos(std::vector<std::string> message);

private:
	Net* m_net;
	std::vector<Entity*> m_players;
	vector<string> m_message;
	std::vector<int> m_playerIDs;
	float elapsedPacketTime;
	void AssignPlayerIDs();
	void SendPlayerPos();
	float Lerp(float a, float b, float f);
};