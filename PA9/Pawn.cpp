#include "Pawn.h"


void Pawn::setPosition(int x, int y)
{
	Shape.setPosition(x, y);
}

sf::ConvexShape Pawn::getKingMarker()
{
	return sf::ConvexShape();
}