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

void Piece::selectPiece()
{
	Shape.setOutlineColor(sf::Color::Yellow);
	Shape.setOutlineThickness(5);
}

void Piece::deselectPiece()
{
	Shape.setOutlineColor(sf::Color::Transparent);
}

std::string Piece::getPieceType()
{
	return pieceType;
}