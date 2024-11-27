	#include "SFML\Graphics.hpp"
	#include "Piece.h"
	#include <iostream>

	int main()
	{

		// Variables, instantiation, etc.

		// Rendering
		sf::RenderWindow window(sf::VideoMode(1600, 1600), "Checkers");
		sf::RectangleShape rect1(sf::Vector2f(200.f,200.f));
		sf::RectangleShape rect2(sf::Vector2f(200.f, 200.f));
		sf::CircleShape P1(100.f);
		sf::CircleShape P2(100.f);

		
		rect1.setFillColor(sf::Color::White);
		rect2.setFillColor(sf::Color::Black);
		P1.setFillColor(sf::Color::Red);
		P1.setFillColor(sf::Color::Blue);


		// Pieces
		Piece* board[8][8] = {nullptr}; // board instantiation, not to be confused with rendering
		int selectedX = 0;
		int selectedY = 0;
		bool isPieceSelected = false;

		// P1 piece placement
		for (int row = 0; row < 3; ++row) 
		{
			for (int col = 0; col < 8; ++col)
			{
				
				if ((row + col) % 2 == 1) // should skip every other row for P1
				{
					board[row][col] = new Piece("red", col * 200, row * 200); 
				}
			}
		}

		// P2 piece placement
		for (int row = 5; row < 8; ++row)
		{
			for (int col = 0; col < 8; ++col)
			{
				if ((row + col) % 2 == 1)
				{
					board[row][col] = new Piece("blue", col * 200, row * 200);
				}
			}
		}

		// Piece rendering using the above 2 piece instantiation loops
		for (int row = 0; row < 8; ++row)
		{
			for (int col = 0; col < 8; ++col)
			{
				if (board[row][col] != nullptr) // Check if a piece exists at this position
				{
					window.draw(board[row][col]->getShape()); // Draw the piece
				}
			}
		}



		// Event loop (while (window.pollEvent(event)) loop) is fundamental to the entire game logic
		// Checks for user events, when an event is registered
		// For example, checking if a key press has registered
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

			// Player 1 Chips
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



			for (int row = 0; row < 8; ++row)
			{
				for (int col = 0; col < 8; ++col)
				{
					delete board[row][col];
					board[row][col] = nullptr;
				}
			}

			window.display();
		}

		return 0;
	}