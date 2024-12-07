#pragma once
#include <SFML/Network.hpp>
#include "Player.h"
#include <iostream>
#include <memory>

class Client
{
public:
	Client();
	Client(sf::IpAddress& ip, unsigned short& port);

	void disconnect(Player* p);

	void send(Player* p);
	void sendPosition(Player* p);
	void receive(Player* p);
	void sendMessage(Player* p, std::string& text);
	void getPlayerList(Player* p);

	std::string getMessage() { 
		return m_textMessage; 
	}


	void runClient();
	bool isRunning = true;
private:
	sf::TcpSocket connection;
	bool m_connected;

	std::string m_textMessage;
	int packetCounter = 0;
	sf::Clock packetClock;
};
