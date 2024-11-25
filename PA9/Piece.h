#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//class for each individual game piece
class Piece
{
protected:
	sf::CircleShape Shape; //includes color of piece, size & position in the window
	std::string pieceType; //"pawn" or "king"
public:
	Piece(std::string newColor = "", int newXCoord = 0, int newYCoord = 0); //constructor
	~Piece(); //destructor

	int getXCoord() const;
	int getYCoord() const;
	sf::CircleShape getShape();
	void setPosition(int x, int y); //changes the position of the shape in the window

	void setColor(std::string newColor); //change color of piece. "red" or "blue
};