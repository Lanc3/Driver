#pragma once

#include <SDL_net.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class Net {
public:
	Net();
	~Net();

	static Net* GetInstance();
	bool Init(const std::string &ip, int32_t remotePort, int32_t localPort);
	void Send(const std::string &str);

	bool CheckForData();

	void SetNoOfPlayers(int value);
	int GetNoOfPlayers();

	bool IsConnected();
	void SetConnected(bool value);

	std::vector<std::string> GetMessage();
	float GetPacketSendInterval();
	
private:
	bool m_connected;
	int m_noOfPlayers;
	float m_packetRate;
	float m_packetSendInterval;

	static Net* m_instance;
	std::vector<std::string> m_message;
	bool m_quit;

	UDPsocket m_socket;
	UDPpacket* m_packet;
	IPaddress m_serverIP;
};