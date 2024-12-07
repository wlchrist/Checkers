#pragma once
#include "Server.h"

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
                        std::cout << "Sorry, the server is full\n";
                        return;
                    }

                    sf::Packet idPacket;
                    idPacket << 0 << m_currentID;
                    newClient->send(idPacket);

                    m_selector.add(*newClient);
                    clients.push_back(std::move(newClient));
                    m_playerNum++;
                    std::cout << "New player connected. ID: " << m_currentID
                        << " Count: " << m_playerNum << "\n";
                    m_currentID++;
                }
            }

            for (std::unique_ptr<sf::TcpSocket>& client : clients) {
                if (m_selector.isReady(*client)) {
                    sf::Packet receivePacket;
                    if (client->receive(receivePacket) == sf::Socket::Done) {
                        // Broadcast to others
                        for (auto& other : clients) {
                            if (other != client) {
                                other->send(receivePacket);
                            }
                        }

                        std::string message;
                        receivePacket >> message;
                        std::cout << "Server received and broadcasted: " << message << "\n";
                    }
                }
            }
        }
    }
}

void Server::sendPacket(sf::Packet& packet, unsigned int skip)
{
    for (unsigned int i = 0; i < m_playerList.size(); ++i)
    {
        if (skip == i)
            continue;
        if (m_playerList[i].getSocket()->send(packet) != sf::Socket::Done)
        {
            std::cout << "Error sending packet in sendPacket func" << std::endl;
        }
    }
}