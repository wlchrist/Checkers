#include "Client.h"
#include "Game.hpp"

Client::Client()
{
}



Client::Client(sf::IpAddress& ip, unsigned short& port) {
    ip = "127.0.0.1";
    port = 54000;
	if (connection.connect(ip, port, sf::seconds(10)) != sf::Socket::Done) {
		std::cout << "Could not connect or connection attempt timed out\n";
	}
	else {
		connection.setBlocking(false);
		std::cout << "Connected successfully. Launching game...\n";
        //Game game;
        //game.runGame();
	}

}

void Client::disconnect(Player* p) {
    connection.disconnect();
    m_connected = false;
}

void Client::send(Player* p) {
    sf::Packet packet;
    packet << p->getID();
    if (connection.send(packet) != sf::Socket::Done) {
        std::cout << "Failed to send packet\n";
    }
}

void Client::receive(Player* p) {
    sf::Packet packet;
    if (connection.receive(packet) == sf::Socket::Done) {
        std::string message;
        packet >> message;
        m_textMessage = message;
    }

}

void Client::runClient() {


    //std::string msg;

    while (isRunning) {
        sf::Packet receivePacket;

        //receiving
        if (connection.receive(receivePacket) == sf::Socket::Done) {
            std::string message;
            receivePacket >> message;
            std::cout << "Received: " << message << "\n";
        }
        // sending
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            sf::Packet sendPacket;
            sendPacket << input;
            connection.send(sendPacket);
        }
    }
}