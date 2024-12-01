#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

// class for each individual game piece
class Piece
{
protected:
	sf::CircleShape Shape; // includes color of piece, size & position in the window
public:
	Piece(sf::Color newColor, int newXCoord = 0, int newYCoord = 0); // constructor
	~Piece(); //destructor
	int getXCoord() const;
	int getYCoord() const;


	sf::Color getColor();

	sf::CircleShape getShape();
	void setPosition(int x, int y);
};