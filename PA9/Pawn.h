#pragma once
#include "Piece.h"

//This class and the 'King' class are subclasses of piece.
class Pawn : public Piece
{
public:
	Pawn(sf::Color newColor, int newXCoord = 0, int newYCoord = 0) : Piece(newColor, newXCoord, newYCoord) {}

	~Pawn();
};

Pawn::~Pawn()
{
}