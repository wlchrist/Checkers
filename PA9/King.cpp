#include "King.h"

inline King::~King()
{
}

inline void King::setStarPosition(int newXCoord, int newYCoord)
{
	KingMarker.setPoint(0, sf::Vector2f(newXCoord + 100, newYCoord + 30));
	KingMarker.setPoint(1, sf::Vector2f(newXCoord + 80, newYCoord + 80));
	KingMarker.setPoint(2, sf::Vector2f(newXCoord + 30, newYCoord + 80));
	KingMarker.setPoint(3, sf::Vector2f(newXCoord + 70, newYCoord + 110));
	KingMarker.setPoint(4, sf::Vector2f(newXCoord + 50, newYCoord + 170));
	KingMarker.setPoint(5, sf::Vector2f(newXCoord + 100, newYCoord + 130));
	KingMarker.setPoint(6, sf::Vector2f(newXCoord + 150, newYCoord + 170));
	KingMarker.setPoint(7, sf::Vector2f(newXCoord + 130, newYCoord + 110));
	KingMarker.setPoint(8, sf::Vector2f(newXCoord + 170, newYCoord + 80));
	KingMarker.setPoint(9, sf::Vector2f(newXCoord + 120, newYCoord + 80));
}

inline void King::setPosition(int x, int y)
{
	Shape.setPosition(x, y);
	setStarPosition(x, y);
}

inline sf::ConvexShape King::getKingMarker()
{
	return KingMarker;
}