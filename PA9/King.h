#pragma once
#include "Piece.h"

//King pieces will contain an outline color of yellow. The outline is drawn when a king piece is initialized
class King : public Piece
{
protected:
	sf::CircleShape KingIcon;
public:
	King(sf::Color newColor, int newXCoord = 0, int newYCoord = 0) : Piece(newColor, newXCoord, newYCoord)
	{
		Shape.setOutlineThickness(10);
		Shape.setOutlineColor(sf::Color::Yellow);
	}

	~King();
};

King::~King()
{
}