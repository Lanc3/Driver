#include "Net.h"

Net* Net::m_instance = nullptr;

Net::Net() 
{
	m_quit = false;
	m_connected = false;
	m_packetRate = 10;
	m_packetSendInterval = (1000.f / m_packetRate) / 1000.f;
}

Net::~Net()
{
	/*SDLNet_FreePacket(m_packet);
	SDLNet_Quit();*/
}

Net* Net::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new Net();
	return m_instance;
}

bool Net::Init(const std::string &ip, int32_t remotePort, int32_t localPort)
{
	std::cout << "Connecting to \n\tIP : " << ip << "\n\tPort : " << remotePort << std::endl;
	std::cout << "Local port : " << localPort << "\n\n";

	if (SDLNet_Init() == -1)
		return false;
	m_socket = SDLNet_UDP_Open(localPort);
	if (m_socket == nullptr)
		return false;
	if (SDLNet_ResolveHost(&m_serverIP, ip.c_str(), remotePort) == -1)
		return false;
	m_packet = SDLNet_AllocPacket(512);
	if (m_packet == nullptr)
		return false;

	m_packet->address.host = m_serverIP.host;
	m_packet->address.port = m_serverIP.port;

	return true;
}

void Net::Send(const std::string &str)
{
	std::string msg = str;
	memcpy(m_packet->data, str.c_str(), str.length());

	m_packet->len = msg.length();

	if (SDLNet_UDP_Send(m_socket, -1, m_packet) == 0)
		std::cout << "\tSDLNet_UDP_Send failed : " << SDLNet_GetError() << "\n";
}

bool Net::CheckForData()
{
	if (SDLNet_UDP_Recv(m_socket, m_packet))
	{
		std::vector<std::string> message;
		Uint8* data = m_packet->data;
		Uint8 len = m_packet->len;

		std::string s(data, data + len);
		std::string value;
		std::istringstream ss(s);

		while (std::getline(ss, value, ',')) {
			message.push_back(value);
		}
		m_message = message;
		return true;
	}
	return false;
}

void Net::SetNoOfPlayers(int value)
{
	m_noOfPlayers = value;
}

int Net::GetNoOfPlayers()
{
	return m_noOfPlayers;
}

bool Net::IsConnected()
{
	return m_connected;
}

void Net::SetConnected(bool value)
{
	m_connected = value;
}

std::vector<std::string> Net::GetMessage()
{
	return m_message;
}

float Net::GetPacketSendInterval()
{
	return m_packetSendInterval;
}
