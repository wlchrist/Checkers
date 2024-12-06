#pragma once
#include "Game.hpp"

int main()
{
    std::cout << "(s)erver or (c)lient or (l)ocal?\n";
    std::string serverOrClient;
    std::getline(std::cin >> std::ws, serverOrClient); // remove whitespace, pass into menu handling below

    if (serverOrClient == "c") {
        sf::IpAddress ip = sf::IpAddress::LocalHost;
        unsigned short port = 54000;
        Client client(ip, port);
        client.runClient();

        //Game game;
        //game.runGame();
    }
    else if (serverOrClient == "s") {
        Server server;
        server.run();
    }
    else if(serverOrClient == "l") {
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