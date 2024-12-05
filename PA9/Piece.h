#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/// class for each individual game piece
class Piece
{
protected:
	sf::CircleShape Shape; // includes color of piece, size & position in the window
	std::string pieceType;
public:
	Piece(sf::Color newColor, int newXCoord = 0, int newYCoord = 0); // constructor
	virtual ~Piece(); //destructor
	int getXCoord() const;
	int getYCoord() const;

	sf::Color getColor();

	sf::CircleShape getShape();
	virtual sf::ConvexShape getKingMarker() = 0; //returns the star shape for king pieces. 
	virtual void setPosition(int x, int y) = 0;

	void selectPiece(); //sets an outline around the piece - color yellow. This indicates that a piece has been selected to move on the board
	void deselectPiece(); //removes outline

	std::string getPieceType();
};