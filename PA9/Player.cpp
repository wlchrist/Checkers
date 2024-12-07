#pragma once
#include "Player.h"

Player::Player(std::unique_ptr<sf::TcpSocket>* socket, sf::Vector2f position, int id)
{
	// Member values
	m_position = position;
	m_name = "Player Name";
	m_id = id;
	m_socket = std::move(*socket);
	m_timeout = sf::seconds(0);
};

	// Getters

	int Player::getID() {
		return m_id;
	}

	sf::TcpSocket* Player::getSocket() {
		return m_socket.get();
	}

	// Setters
	void Player::setPosition(sf::Vector2f position) {
		m_position = position;
	}

	void Player::setPosition(float x, float y) {
		m_position.x = x;
		m_position.y = y;
	}

	sf::Vector2f Player::getPosition()
	{
		return sf::Vector2f();
	}



	// Update method
	void Player::update(float deltaTime) {
		// Implement update logic here
	}

