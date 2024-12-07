#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "Player.h"


// Server
class Server {

public:
	
	Server();
	void run();
private:
	void sendPacket(sf::Packet& packet, unsigned int skip = -1);
	bool m_isRunning;
	sf::IpAddress m_ipAddress;
	unsigned short m_port;
	sf::TcpListener m_listener;
	sf::SocketSelector m_selector;
	int m_maxPlayerNum;
	int m_currentID;
	int m_playerNum;
	char m_tmp[1400];
	std::vector<Player> m_playerList;
	sf::Clock clock;
};