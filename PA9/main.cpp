#include "SFML\Graphics.hpp"
#include "Pawn.h"
#include "King.h"
#include <iostream>
#include "stateMachine.h"

int main()
{
	//updated by NOAH 11/28/2024 just a version verifier feel free to overwrite if you change anything im just parinoid about pulling and old version lol

	//updataed by BEN 11/30/2024 added subclasses for pawn and king pieces. Also fixed rendering pieces to the board after memory for creating pieces was allocated. 

	//updated by NOAH 12/1/2024 finished piece movemnet logic attmepted to fix issue with piece rendering , added escape clause to deselect pieces.

	// Variables, instantiation, etc.

	// Rendering
	sf::RenderWindow window(sf::VideoMode(1600, 1600), "Checkers");
	sf::RectangleShape rect1(sf::Vector2f(200.f, 200.f));
	sf::RectangleShape rect2(sf::Vector2f(200.f, 200.f));
	sf::CircleShape P1(100.f);
	sf::CircleShape P2(100.f);
	gameState currentState = pieceSelection;


	rect1.setFillColor(sf::Color::Red);
	rect2.setFillColor(sf::Color::Black);
	P1.setFillColor(sf::Color::White);
	P2.setFillColor(sf::Color::Red);//changed to p2 Noah

	//gameState currentState = pieceSelection;//state machine initalization Noah

	// Pieces
	Piece* board[8][8] = { nullptr }; // board instantiation, not to be confused with rendering
	int selectedX = 0;
	int selectedY = 0;
	bool isPieceSelected = false;

	int col = 0;
	int row = 0;

	// P1 piece placement
	for (int row = 0; row < 2; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if ((row + col) % 2 == 1) // should skip every other row for P1
			{
				board[row][col] = new Pawn(sf::Color::White, col * 200, row * 200);
			}
		}
	}

	// P2 piece placement
	for (int row = 6; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if ((row + col) % 2 == 1)
			{
				board[row][col] = new Pawn(sf::Color::Red, col * 200, row * 200);
			}
		}
	}

	//can be removed in post just tests piece loactions -Noah
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
				std::cout << "its broke" << std::endl;
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
		float rad = P1.getRadius();
		//end Blame
		sf::Event event;

	
	
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && currentState == pieceMove) //deselectes piece with escape
			{
				if (event.key.code == 36)
				{
					board[row][col]->deselectPiece();
					selectedCol = -1;
					selectedRow = -1;
					currentState = pieceSelection;
					std::cout << "Piece deselected.\n";
				}

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

					col = mouseX / tileSizeX;// divide X click coords by curent X tile size to accurelty get array coords
					row = mouseY / tileSizeY;// divide Y click coords by curent Y tile size to accurelty get array coords

					float colAC = static_cast<float>(col);//1
					float rowAC = static_cast<float>(row);//2
					
					float centerX = colAC * tileSizeX + (tileSizeX - rad) / 2;//3
					float centerY = rowAC * tileSizeY + (tileSizeY - rad) / 2;//4
					//1-4 are attempts to constrain piece placment for more accurate visuals
					
					if (currentState == pieceSelection && board[row][col] != NULL)
					{
						//Set piece as selected
						board[row][col]->selectPiece();

						selectedPiece = board[row][col];
						selectedCol = col;
						selectedRow = row;
						currentState = pieceMove;
						std::cout << "Selected piece at: (" << col << "," << row << ")\n" << std::endl;
					}
					else if (currentState == pieceMove && board[row][col] == nullptr)
					{
						int rowDiff = abs(row - selectedRow);
						int colDiff = abs(col - selectedCol);

						if (rowDiff == 1 && colDiff == 1)
						{
							//piece movment
							selectedPiece->setPosition(centerX-50, centerY-50);//controls visual repersentation
							board[row][col] = selectedPiece;
							board[selectedRow][selectedCol] = nullptr;

							
							//state reset
							selectedPiece = nullptr;
							selectedCol = -1;
							selectedRow = -1;
							currentState = pieceSelection;

							board[row][col]->deselectPiece();

							std::cout << "moved piece to: (" << col << "," << row << ")\n" << std::endl;
						}

						// detecting if user can take a piece here - Warren
						// seems like piece placement should be reworked so pieces can be taken
						else if (rowDiff == abs(2) && colDiff == abs(2)) { // if there is a difference of 2 (absolute val) between your piece and the enemys piece
							// we will de-render the piece being taken 


							// piece movement, similar to the above
							selectedPiece->setPosition(centerX -50, centerY -50);
							board[row][col] = selectedPiece;
							board[selectedRow][selectedCol] = nullptr;
							board[selectedRow + 1][selectedCol + 1] = nullptr;
							// state reset
							selectedPiece = nullptr;
							selectedCol = -1;
							selectedRow = -1;
							currentState = pieceSelection;
							
							board[row][col]->deselectPiece();
						}

						else {
							std::cout << "Invalid move! Diagonal moves only.\n";
						}
					}
					

					else if (currentState == pieceMove && board[row][col] != nullptr)
					{
						std::cout << "Cannot move here; tile (" << col << "," << row << ") is occupied.\n";
					}
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

		//This loop renders the pieces in the window
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

		window.display();
	}

	return 0;
}