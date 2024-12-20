#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

inline void gameOver(sf::Color CurrentPlayer) {
    sf::Text gameOver;
    sf::Font gameOverFont;
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Game Over");

    if (gameOverFont.loadFromFile("C:/Windows/Fonts/arial.ttf") == false) {
        std::cout << "Could not load font from file";
        return;
    }
    sf::FloatRect textRect = gameOver.getLocalBounds();
    gameOver.setOrigin(textRect.left + textRect.width / 2.0f,
    textRect.top + textRect.height / 2.0f);
    gameOver.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    gameOver.setFont(gameOverFont);

    if (CurrentPlayer == sf::Color::Red)
    {
        gameOver.setString("GAME OVER\n  Red Wins");
    }
    else
    {
        gameOver.setString("GAME OVER\nWhite Wins");
    }
    
    gameOver.setCharacterSize(72);
    gameOver.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(gameOver);
        window.display();
    }
}