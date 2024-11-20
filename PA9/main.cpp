#include "SFML\Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 1600), "Checkers");
	sf::RectangleShape rect1(sf::Vector2f(200.f,200.f));
	sf::RectangleShape rect2(sf::Vector2f(200.f, 200.f));
	sf::CircleShape P1(100.f);
	sf::CircleShape P2(100.f);


	rect1.setFillColor(sf::Color::White);
	rect2.setFillColor(sf::Color::Black);
	P1.setFillColor(sf::Color::Red);
	P1.setFillColor(sf::Color::Blue);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// Checkerboard code
		for (int boardx = 0; boardx < 1600; boardx = boardx + 400)
		{
			for (int boardy = 0; boardy < 1600; boardy = boardy + 400)
			{
				rect1.setPosition(boardx, boardy);
				window.draw(rect1);
			}
		}

		for (int boardx = 200; boardx < 1600; boardx = boardx + 400)
		{
			for (int boardy = 200; boardy < 1600; boardy = boardy + 400)
			{
				rect1.setPosition(boardx, boardy);
				window.draw(rect1);
			}
		}

		for (int boardx = 200; boardx < 1600; boardx = boardx + 400)
		{
			for (int boardy = 0; boardy < 1600; boardy = boardy + 400)
			{
				rect2.setPosition(boardx, boardy);
				window.draw(rect2);
			}
		}

		for (int boardx = 0; boardx < 1600; boardx = boardx + 400)
		{
			for (int boardy = 200; boardy < 1600; boardy = boardy + 400)
			{
				rect2.setPosition(boardx, boardy);
				window.draw(rect2);
			}
		}

		//Player 1 Chips
		for (int coordx = 200; coordx < 1600; coordx = coordx + 400)
		{
			P1.setPosition(coordx, 0);
			window.draw(P1);
		}

		for (int coordx = 0; coordx < 1600; coordx = coordx + 400)
		{
				P1.setPosition(coordx, 200);
				window.draw(P1);
		}
		
		window.display();
	}

	return 0;
}