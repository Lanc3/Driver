#include "MultiplayerSystem.h"

MultiplayerSystem::MultiplayerSystem()
{
	m_net = Net::GetInstance();
}

MultiplayerSystem::MultiplayerSystem(std::vector<Entity*> players)
{
	m_net = Net::GetInstance();
	m_players = players;
	AssignPlayerIDs();
	elapsedPacketTime = 0;
}

MultiplayerSystem::~MultiplayerSystem()
{
}

void MultiplayerSystem::Update(float dt)
{
	elapsedPacketTime += dt;
	if (m_net->CheckForData())
	{
		m_message = m_net->GetMessage();
		UpdatePos(m_message); //lerp
		elapsedPacketTime = 0;
	}
	SendPlayerPos();
}

void MultiplayerSystem::UpdatePos(std::vector<std::string> message)
{
	float percent = elapsedPacketTime / m_net->GetPacketSendInterval();
	for (Entity* e : m_players)
	{
		if (message[0] == "player")
		{
			if (std::find(m_playerIDs.begin(), m_playerIDs.end(), atoi(message[1].c_str())) != m_playerIDs.end()) {
			}
			else
			{
				for (int i = 0; i < m_players.size(); i++)
				{
					if (m_players[i]->playerSet == false)
					{
						m_players[i]->id = atoi(message[1].c_str());
						m_playerIDs.push_back(atoi(message[1].c_str()));
						m_players[i]->playerSet = true;
						break;
					}
				}
			}
			if (e->id == atoi(message[1].c_str()))
			{
				Transformable* t = (Transformable*)e->GetComponent("transformable");
				if (t != nullptr)
				{
					t->m_yaw = Lerp(t->m_yaw, atoi(message[5].c_str()), percent);
					t->m_position = glm::vec3
					(
						Lerp(t->m_position.x, atoi(message[2].c_str()), percent),
						Lerp(t->m_position.y, atoi(message[3].c_str()), percent),
						Lerp(t->m_position.z, atoi(message[4].c_str()), percent)
					);
				}
				break;
			}
		}
	}
}

void MultiplayerSystem::SendPlayerPos()
{
	Transformable* t = (Transformable*)m_players[0]->GetComponent("transformable");
	m_net->Send("player," + to_string(m_players[0]->id) + "," + to_string(t->m_position.x) + "," + to_string(t->m_position.y) + "," + to_string(t->m_position.z) + "," + to_string(t->m_yaw));
}

void MultiplayerSystem::AssignPlayerIDs()
{
	vector<string> message = m_net->GetMessage();
	if (!message.empty())
	{
		if (message[0] == "player")
		{
			
		}
	}
}

float MultiplayerSystem::Lerp(float a, float b, float f)
{
	return (a * (1.0f - f)) + (b * f);
}
