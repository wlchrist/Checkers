#pragma once
#include "Game.hpp"

int main()
{
    std::cout << "Press (1) to run game locally\nPress (2) to host a server (Extra Credit)\nPress (3) to start a networked client instance (Extra Credit)\n";
    std::string serverOrClient;
    std::getline(std::cin >> std::ws, serverOrClient);
    if (serverOrClient == "3") {
        Server server;
        server.run();
    }
    else if (serverOrClient == "2") {
        sf::IpAddress ip = sf::IpAddress::LocalHost;
        unsigned short port = 54000;
        Client client(ip, port);
        client.runClient();
    }
    else if(serverOrClient == "1") {
        Game game;
        game.runGame();
    }
    else {
        std::cout << "Invalid input, running game locally\n";
        Game game;
        game.runGame();
    }

	return 0;
}