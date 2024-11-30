	#include "SFML\Graphics.hpp"
	#include "Piece.h"
	#include <iostream>
	#include "stateMachine.h"

	int main()
	{
		//updated by NOAH 11/28/2024 just a version verifier feel free to overwrite if you change anything im just parinoid about pulling and old version lol
		
		// Variables, instantiation, etc.

		// Rendering
		sf::RenderWindow window(sf::VideoMode(1600, 1600), "Checkers");
		sf::RectangleShape rect1(sf::Vector2f(200.f,200.f));
		sf::RectangleShape rect2(sf::Vector2f(200.f, 200.f));
		sf::CircleShape P1(100.f);
		sf::CircleShape P2(100.f);

		
		rect1.setFillColor(sf::Color::White);
		rect2.setFillColor(sf::Color::Black);
		P1.setFillColor(sf::Color::Blue);
		P2.setFillColor(sf::Color::Red);//changed to p2 Noah

		gameState currentState = pieceSelection;//state machine initalization Noah

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
					board[row][col] = new Piece("blue", col * 200, row * 200); 
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
					board[row][col] = new Piece("red", col * 200, row * 200);
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

		//int i = 0, j = 0;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == nullptr)
				{
					//std::cout << "no piece here (" << i << "," << j << ")\n" << std::endl;


				}
				else if (board[i][j] != nullptr)
				{
					std::cout << "piece here (" << i << "," << j << ")\n" << std::endl;
				}
				else
				{
					std::cout << "shits broke" << std::endl;
				}
			}

		}
	

		Piece* selectedPiece = nullptr;
		int selectedRow = -1, selectedCol = -1;

		// Event loop (while (window.pollEvent(event)) loop) is fundamental to the entire game logic
		// Checks for user events, when an event is registered
		// For example, checking if a key press has registered
		while (window.isOpen())
		{
			//Blame Noah 
			const int BOARD_SIZE = 8;
			int mouseX = 0;
			int mouseY = 0;
			int selectedRow = -1;
			int selectedCol = -1;
			Piece* selectedPiece = nullptr;
			//end Blame
			sf::Event event;


			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::MouseButtonPressed)//Blame Noah 
				{
					if (event.mouseButton.button == sf::Mouse::Left)//checks for left click
					{
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);//gets mouse postition in vector form

						mouseX = mousePosition.x;//sets x mouse coord
						mouseY = mousePosition.y;//sets y mouse coord

						float tileSizeX = window.getSize().x / BOARD_SIZE;//get current tile size y
						float tileSizeY = window.getSize().y / BOARD_SIZE;//get current tile size x

						int col = mouseX / tileSizeX;// divide X click coords by curent X tile size to accurelty get array coords
						int row = mouseY / tileSizeY;// divide Y click coords by curent Y tile size to accurelty get array coords

						//commented code below needs testing once pieces can be found -Noah
						if (currentState == pieceSelection)
						{

							if (board[row][col] != nullptr)//"board[row][col] != nullptr" references to there being a "Piece" at the specifed coords
							{
								selectedPiece = board[row][col];
								selectedRow = row;
								selectedCol = col;
								currentState = pieceMove;
								std::cout << "The Piece you have selected is at: (" << selectedRow << "," << selectedCol << ")\n" << std::endl;

							}
						}
						else if(currentState == pieceMove)
						{
							if (board[row][col] == nullptr && selectedPiece != nullptr)//"board[row][col] == nullptr" references to there not being a "Piece" at the specifed coords
							{
								selectedPiece->setPosition(col * tileSizeX, row * tileSizeY);

								std::cout << "broke 120 \n";//BROKEN HERE

								board[row][col] = selectedPiece;
								board[selectedRow][selectedCol] = nullptr;


								selectedPiece = nullptr;
								selectedCol = -1;
								selectedRow = -1;
								currentState = pieceSelection;

								std::cout << "Moved selected piece to: (" << row << "," << col << ")\n" << std::endl;
							}

						}
						else
						{
							std::cout << "no piece selected \n" << std::endl;
							//std::cout << "Invalid movement Piece deselected please try again \n" << std::endl;
						/*	std::cout << "broke 131 \n";
							selectedPiece = nullptr;
							selectedCol = -1;
							selectedRow = -1;*/
						}
						
						//this code is funcional

						//if (board[row][col] != nullptr)//checks if point has a piece
						//{//true
						//	board[row][col]->setPosition(mouseX, mouseY);
						//	std::cout << "Mouse is at: (" << row << "," << col << ")\n" << std::endl;
						//}
						//else if (board[row][col] == nullptr)
						//{//false
						//	std::cout << "Invalid click no piece at tile (" << row << "," << col << ")\n" << std::endl;
						//}
					}

				}


			}//end Blame



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

			//these two blocks are actually hadling the rendering but may be hard coded -Noah

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
			for (int coordx = 200; coordx < 1600; coordx = coordx + 400)
			{
				P1.setPosition(coordx, 400);
				window.draw(P1);
			}


			// Player 2 Chips
			for (int coordx = 0; coordx < 1600; coordx = coordx + 400)
			{
				P2.setPosition(coordx, 1400);
				window.draw(P2);
			}
			for (int coordx = 200; coordx < 1600; coordx = coordx + 400)
			{
				P2.setPosition(coordx, 1200);
				window.draw(P2);
			}
			for (int coordx = 0; coordx < 1600; coordx = coordx + 400)
			{
				P2.setPosition(coordx, 1000);
				window.draw(P2);
			}

			//leave commented out for now constant board deletion prevents player actions from being read -Noah

			/*for (int row = 0; row < 8; ++row)
			{
				for (int col = 0; col < 8; ++col)
				{
					delete board[row][col];
					board[row][col] = nullptr;
				}
			}*/

			window.display();
		}

		return 0;
	}