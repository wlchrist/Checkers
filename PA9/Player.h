#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

class Player {
public:
	Player(std::unique_ptr<sf::TcpSocket>* socket, sf::Vector2f position, int id);


	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	int getID();
	sf::TcpSocket* getSocket();
	void update(float deltaTime);

private:
	sf::Vector2f m_position;
	int m_id;
	std::string m_name;
	std::unique_ptr<sf::TcpSocket> m_socket = nullptr;
	sf::Time m_timeout;
};