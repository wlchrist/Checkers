#include "Piece.h"


Piece::Piece(std::string newColor, int newXCoord, int newYCoord)
{
	Shape.setPosition(newXCoord, newYCoord);
	Shape.setRadius(100.f);
	setColor(newColor);
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


void Piece::setPosition(int x, int y)
{
	Shape.setPosition(x, y);
}

sf::CircleShape Piece::getShape()
{
	return Shape;
}

void Piece::setColor(std::string newColor)
{
	/*
	NOTE: if someone finds a better way to change the color of a piece, feel free to rewrite it
	*/
	if (newColor == "red")
	{
		Shape.setFillColor(sf::Color::Red);
	}
	else if (newColor == "blue")
	{
		Shape.setFillColor(sf::Color::Blue);
	}

}




// movement logic
void Piece::movePiece(int x, int y)
{

	setPosition(x, y);
}

