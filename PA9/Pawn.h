#pragma once
#include "Piece.h"

//This class and the 'King' class are subclasses of piece.
class Pawn : public Piece
{
public:
	Pawn(sf::Color newColor, int newXCoord = 0, int newYCoord = 0) : Piece(newColor, newXCoord, newYCoord) {}
	/*~Pawn();*/

	void setPosition(int x, int y);
	sf::ConvexShape getKingMarker(); //returns nothing for this class. It needs to be here to run properly 
};
