#include "Piece.h"


Piece::Piece(sf::Color newColor, int newXCoord, int newYCoord)
{
	Shape.setPosition(newXCoord, newYCoord);
	Shape.setRadius(100.f);
	Shape.setFillColor(newColor);
}

Piece::~Piece()
{
}

int Piece::getXCoord() const
{
	return Shape.getPosition().x;
}

int Piece::getYCoord() const
{
	return Shape.getPosition().y;
}

sf::Color Piece::getColor()
{
	return Shape.getFillColor();
}

sf::CircleShape Piece::getShape()
{
	return Shape;
}

void Piece::setPosition(int x, int y)
{
	Shape.setPosition(x, y);
}