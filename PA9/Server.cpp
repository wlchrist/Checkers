#pragma once
#include "Server.h"
#include "Game.hpp"

Server::Server() {

	m_maxPlayerNum = 2;
	m_currentID = 0;
	m_playerNum = 0;
	m_isRunning = true;
	m_listener.listen(54000);
	m_selector.add(m_listener);


}



void Server::run() {
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;

    while (m_isRunning) {
        if (m_selector.wait()) {
            if (m_selector.isReady(m_listener)) {
                std::unique_ptr<sf::TcpSocket> newClient = std::make_unique<sf::TcpSocket>();

                if (m_listener.accept(*newClient) == sf::Socket::Done) {



                    if (m_playerNum >= m_maxPlayerNum) {
                        sf::Packet fullPacket;
                        fullPacket << 2 << 0;
                        newClient->send(fullPacket);
                        std::cout << "server is full\n";
                        return;
                    }

                    sf::Packet idPacket;
                    idPacket << 0 << m_currentID;
                    newClient->send(idPacket);

                    m_selector.add(*newClient);
                    clients.push_back(std::move(newClient));
                    m_playerNum++;
                    std::cout << "New player connected WITH ID: " << m_currentID
                        << " player count: " << m_playerNum << "\n";
                    m_currentID++;
                }
            }

            for (std::unique_ptr<sf::TcpSocket>& client : clients) {
                if (m_selector.isReady(*client)) {
                    sf::Packet receivePacket;
                    if (client->receive(receivePacket) == sf::Socket::Done) {

                        // currently not broadcasting to all clients when received
                        // messages are only received AFTER client sends a message
                        // in other words, messages are received out of order
                        // obviously, this should not happen
                        for (auto& other : clients) {
                            if (other != client) {
                                other->send(receivePacket);
                            }
                        }

                        std::string message;
                        receivePacket >> message;
                        std::cout << "Server received message and broadcasted: " << message << "\n";
                        std::string msg = message;
                    }
                }
            }
        }
    }
}

