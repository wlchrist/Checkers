#include <iostream>
#include "SFML\Graphics.hpp"
#include "Pawn.h"
#include "King.h"
#include "StateMachine.h"
#include "Rules.h"
#include "GameOverComponent.h"

void main()
{
	//updated by NOAH 11/28/2024 just a version verifier feel free to overwrite if you change anything im just parinoid about pulling and old version

	//updataed by BEN 11/30/2024 added subclasses for pawn and king pieces. Also fixed rendering pieces to the board after memory for creating pieces was allocated. 

	//updated by NOAH 12/1/2024 finished piece movement logic attmepted to fix issue with piece rendering , added escape clause to deselect pieces.

	//updated by BEN 12/2/2024 resolved issue where pieces were not aligned with squares on board

	//updated by WARREN 12/3/2024 added feature which handles piece-taking, added feature which promotes pawn to king, added feature which checks for win.
	
	//updated by WARREN 12/4/2024 fixed an issue where game-over was not working
	
	// Variables, instantiation, etc.

	// Rendering


	
	sf::RenderWindow window(sf::VideoMode(1600, 1600), "Checkers");
	sf::RectangleShape rect1(sf::Vector2f(200.f, 200.f));
	sf::RectangleShape rect2(sf::Vector2f(200.f, 200.f));
	sf::CircleShape P1(100.f);
	sf::CircleShape P2(100.f);
	gameState currentState = pieceSelection;


	rect1.setFillColor(sf::Color::White);
	rect2.setFillColor(sf::Color::Black);
	P1.setFillColor(sf::Color::White);
	P2.setFillColor(sf::Color::Red);//changed to p2 Noah

	// Pieces
	Piece* board[8][8] = { nullptr }; // board instantiation, not to be confused with rendering
	int selectedX = 0;
	int selectedY = 0;
	bool isPieceSelected = false;

	int col = 0;
	int row = 0;

	sf::Color currentPlayer = sf::Color::White; // white should go first



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




	Piece* selectedPiece = nullptr;
	int selectedRow = -1, selectedCol = -1;

	// Event loop (while (window.pollEvent(event)) loop) is FUNDAMENTAL to the entire game logic
	// Checks for user events, when an event is registered
	// (For example, checking if a key press has registered)
	while (window.isOpen())
	{
		const int BOARD_SIZE = 8;
		int mouseX = 0;
		int mouseY = 0;
		float rad = P1.getRadius();
		sf::Event event;

	
	
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && currentState == pieceMove) // Deselects piece with escape
			{
				if (event.key.code == 36)
				{
					
					selectedCol = -1;
					selectedRow = -1;
					currentState = pieceSelection;
					std::cout << "Piece deselected.\n";
					selectedPiece->deselectPiece();
				}

			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)// checks for left click
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);// gets mouse postition in vector form

					mouseX = mousePosition.x;// sets x mouse coord
					mouseY = mousePosition.y;// sets y mouse coord

					float tileSizeX = window.getSize().x / BOARD_SIZE;// get current tile size y
					float tileSizeY = window.getSize().y / BOARD_SIZE;// get current tile size x

					col = mouseX / tileSizeX;// divide X click coords by curent X tile size to accurelty get array coords
					row = mouseY / tileSizeY;// divide Y click coords by curent Y tile size to accurelty get array coords

					float colAC = static_cast<float>(col);
					float rowAC = static_cast<float>(row);
					
					float centerX = colAC * tileSizeX + (tileSizeX - rad) / 2;
					float centerY = rowAC * tileSizeY + (tileSizeY - rad) / 2;
					// 1-4 are attempts to constrain piece placment for more accurate visuals
					
					
					// Piece selection code block
					if (currentState == pieceSelection && board[row][col] != NULL)
					{

						// Validates if whose turn it is using function from Rules.h
						if (!isValidTurn(board[row][col], currentPlayer)) {
							if (currentPlayer == sf::Color::White) {
								std::cout << "White must move\n";

							}
							else {
								std::cout << "Red must move\n";
							}
							
						}
						else {
							// Set piece as selected
							board[row][col]->selectPiece();

							selectedPiece = board[row][col];
							selectedCol = col;
							selectedRow = row;
							currentState = pieceMove;
							std::cout << "Selected piece at: (" << col << "," << row << ")\n" << std::endl;
						}
					}
					else if (currentState == pieceMove && board[row][col] == nullptr /*tile they selected to move to is empty*/)
					{
						int rowDiff = abs(row - selectedRow);
						int colDiff = abs(col - selectedCol);

						//which player is moving. Red or white?
						if (selectedPiece->getColor() == sf::Color::Red)
						{
							//red
							//king or pawn?
							if (selectedPiece->getPieceType() == "king")
							{
								//king piece is moving
								cout << selectedPiece->getPieceType() << endl;

								//player is allowed to move in any direction

								//are they moving one tile or tryin to capture a piece
								if (rowDiff == 1 && colDiff == 1)
								{
									//moving by one tile
									//king can move in any diagonal direction
									selectedPiece->setPosition(centerX - 50, centerY - 50); // controls visual repersentation
									board[row][col] = selectedPiece;
									board[selectedRow][selectedCol] = nullptr;

									// Check for win conditions
										// TODO: render an overlay with the player which won
									if (didWin(board, selectedPiece->getColor())) {
										std::cout << "Game Over\n";
										gameOver();
									}

									//state reset
									selectedPiece->deselectPiece();
									selectedPiece = nullptr;
									selectedCol = -1;
									selectedRow = -1;
									currentState = pieceSelection;

									// now switch turns
									currentPlayer = sf::Color::White;
									std::cout << "Turn switched to White\n";

								}
								else if (rowDiff == 2 && colDiff == 2)
								{
									//trying to capture a piece
									int capturedRow = selectedRow + (row - selectedRow) / 2;
									int capturedCol = selectedCol + (col - selectedCol) / 2;

									//is the tile that the piece they are trying to capture valid for capture? is there a piece? is it from the opposing side?
									if (board[capturedRow][capturedCol] != nullptr &&
										board[capturedRow][capturedCol]->getColor() != selectedPiece->getColor()) {

										selectedPiece->setPosition(centerX - 50, centerY - 50);
										board[row][col] = selectedPiece;
										board[selectedRow][selectedCol] = nullptr;
										delete board[capturedRow][capturedCol];
										board[capturedRow][capturedCol] = nullptr;

										// Check for win conditions
										// TODO: render an overlay with the player which won
										if (didWin(board, selectedPiece->getColor())) {
											std::cout << "Game Over\n";
											gameOver();
										}

										//state reset
										selectedPiece->deselectPiece();
										selectedPiece = nullptr;
										selectedCol = -1;
										selectedRow = -1;
										currentState = pieceSelection;

										

										std::cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

										

										// now switch turns
										currentPlayer = sf::Color::White;
										std::cout << "Turn switched to White\n";
										
									}
									else
									{
										std::cout << "Cannot capture piece here\n";
									}
								}
								else if (rowDiff != colDiff)
								{
									std::cout << "Make sure to only move diagonally\n";
								}
								else
								{
									cout << "you cannot move that far\n";
								}
							}
							else
							{
								//pawn is moving
								cout << selectedPiece->getPieceType() << endl;

								//is the direction they are moving viable for the player?
								//Red: they can only move foward
								if (row > selectedRow)
								{
									std::cout << "Red can only move up\n";
								}
								else
								{
									//they are moving up
									if (rowDiff == 1 && colDiff == 1)
									{
										// piece movement
										selectedPiece->setPosition(centerX - 50, centerY - 50); // controls visual repersentation
										board[row][col] = selectedPiece;
										board[selectedRow][selectedCol] = nullptr;
										// We want to continuously check if king promotion is possible
										if (row == 0)
										{
											// King piece creation here
											King* kingPiece = new King(selectedPiece->getColor(), centerX
												- 50, centerY - 50);

											// replacing pawn with king
											delete board[row][col];
											board[row][col] = kingPiece;

										}

										// Check for win conditions
										// TODO: render an overlay with the player which won
										if (didWin(board, selectedPiece->getColor())) {
											std::cout << "Game Over\n";
											gameOver();
										}

										// state reset
										selectedPiece->deselectPiece();
										selectedPiece = nullptr;
										selectedCol = -1;
										selectedRow = -1;
										currentState = pieceSelection;

										std::cout << "moved piece to: (" << col << "," << row << ")\n" << std::endl;

										// now switch turns
										currentPlayer = sf::Color::White;
										std::cout << "Turn switched to White\n";
										
										
									}
									else if (rowDiff == 2 && colDiff == 2)
									{
										//trying to capture a piece
										int capturedRow = selectedRow + (row - selectedRow) / 2;
										int capturedCol = selectedCol + (col - selectedCol) / 2;

										//is the tile that the piece they are trying to capture valid for capture? is there a piece? is it from the opposing side?
										if (board[capturedRow][capturedCol] != nullptr &&
											board[capturedRow][capturedCol]->getColor() != selectedPiece->getColor()) {

											selectedPiece->setPosition(centerX - 50, centerY - 50);
											board[row][col] = selectedPiece;
											board[selectedRow][selectedCol] = nullptr;
											delete board[capturedRow][capturedCol];
											board[capturedRow][capturedCol] = nullptr;

											// We want to continuously check if king promotion is possible
											if (row == 0)
											{
												// King piece creation here
												King* kingPiece = new King(selectedPiece->getColor(), centerX
													- 50, centerY - 50);

												// replacing pawn with king
												delete board[row][col];
												board[row][col] = kingPiece;

											}

											// Check for win conditions
										// TODO: render an overlay with the player which won
											if (didWin(board, selectedPiece->getColor())) {
												std::cout << "Game Over\n";
												gameOver();
											}

											//state reset
											selectedPiece->deselectPiece();
											selectedPiece = nullptr;
											selectedCol = -1;
											selectedRow = -1;
											currentState = pieceSelection;

											

											std::cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

											// now switch turns
											currentPlayer = sf::Color::White;
											std::cout << "Turn switched to White\n";
										}
										else
										{
											std::cout << "Cannot capture piece here\n";
										}

									}
									else if (rowDiff != colDiff)
									{
										std::cout << "Make sure to only move diagonally\n";
									}
									else
									{
										cout << "you cannot move that far\n";
									}
								}
							}
						}
						else if (selectedPiece->getColor() == sf::Color::White)
						{
							//red
							//king or pawn?
							if (selectedPiece->getPieceType() == "king")
							{
								//king piece is moving
								cout << selectedPiece->getPieceType() << endl;

								//player is allowed to move in any direction

								//are they moving one tile or tryin to capture a piece
								if (rowDiff == 1 && colDiff == 1)
								{
									//moving by one tile
									//king can move in any diagonal direction
									selectedPiece->setPosition(centerX - 50, centerY - 50); // controls visual repersentation
									board[row][col] = selectedPiece;
									board[selectedRow][selectedCol] = nullptr;

									// Check for win conditions
										// TODO: render an overlay with the player which won
									if (didWin(board, selectedPiece->getColor())) {
										std::cout << "Game Over\n";
										gameOver();
									}

									//state reset
									selectedPiece->deselectPiece();
									selectedPiece = nullptr;
									selectedCol = -1;
									selectedRow = -1;
									currentState = pieceSelection;

									// now switch turns
									currentPlayer = sf::Color::Red;
									std::cout << "Turn switched to Red\n";

								}
								else if (rowDiff == 2 && colDiff == 2)
								{
									//trying to capture a piece
									int capturedRow = selectedRow + (row - selectedRow) / 2;
									int capturedCol = selectedCol + (col - selectedCol) / 2;

									//is the tile that the piece they are trying to capture valid for capture? is there a piece? is it from the opposing side?
									if (board[capturedRow][capturedCol] != nullptr &&
										board[capturedRow][capturedCol]->getColor() != selectedPiece->getColor()) {

										selectedPiece->setPosition(centerX - 50, centerY - 50);
										board[row][col] = selectedPiece;
										board[selectedRow][selectedCol] = nullptr;
										delete board[capturedRow][capturedCol];
										board[capturedRow][capturedCol] = nullptr;

										// Check for win conditions
										// TODO: render an overlay with the player which won
										if (didWin(board, selectedPiece->getColor())) {
											std::cout << "Game Over\n";
											gameOver();
										}

										//state reset
										selectedPiece->deselectPiece();
										selectedPiece = nullptr;
										selectedCol = -1;
										selectedRow = -1;
										currentState = pieceSelection;



										std::cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

										// now switch turns
										currentPlayer = sf::Color::Red;
										std::cout << "Turn switched to Red\n";

									}
									else
									{
										std::cout << "Cannot capture piece here\n";
									}
								}
								else if (rowDiff != colDiff)
								{
									std::cout << "Make sure to only move diagonally\n";
								}
								else
								{
									cout << "you cannot move that far\n";
								}
							}
							else
							{
								//pawn is moving
								cout << selectedPiece->getPieceType() << endl;

								//is the direction they are moving viable for the player?
								//White: can only move down
								if (row < selectedRow)
								{
									std::cout << "White can only move up\n";
								}
								else
								{
									//they are moving up
									if (rowDiff == 1 && colDiff == 1)
									{
										// piece movement
										selectedPiece->setPosition(centerX - 50, centerY - 50); // controls visual repersentation
										board[row][col] = selectedPiece;
										board[selectedRow][selectedCol] = nullptr;
										// We want to continuously check if king promotion is possible
										if (row == 7)
										{
											// King piece creation here
											King* kingPiece = new King(selectedPiece->getColor(), centerX
												- 50, centerY - 50);

											// replacing pawn with king
											delete board[row][col];
											board[row][col] = kingPiece;

										}

										// Check for win conditions
										// TODO: render an overlay with the player which won
										if (didWin(board, selectedPiece->getColor())) {
											std::cout << "Game Over\n";
											gameOver();
										}

										// state reset
										selectedPiece->deselectPiece();
										selectedPiece = nullptr;
										selectedCol = -1;
										selectedRow = -1;
										currentState = pieceSelection;

										std::cout << "moved piece to: (" << col << "," << row << ")\n" << std::endl;

										// now switch turns
										currentPlayer = sf::Color::Red;
										std::cout << "Turn switched to Red\n";


									}
									else if (rowDiff == 2 && colDiff == 2)
									{
										//trying to capture a piece
										int capturedRow = selectedRow + (row - selectedRow) / 2;
										int capturedCol = selectedCol + (col - selectedCol) / 2;

										//is the tile that the piece they are trying to capture valid for capture? is there a piece? is it from the opposing side?
										if (board[capturedRow][capturedCol] != nullptr &&
											board[capturedRow][capturedCol]->getColor() != selectedPiece->getColor()) {

											selectedPiece->setPosition(centerX - 50, centerY - 50);
											board[row][col] = selectedPiece;
											board[selectedRow][selectedCol] = nullptr;
											delete board[capturedRow][capturedCol];
											board[capturedRow][capturedCol] = nullptr;

											// We want to continuously check if king promotion is possible
											if (row == 7)
											{
												// King piece creation here
												King* kingPiece = new King(selectedPiece->getColor(), centerX
													- 50, centerY - 50);

												// replacing pawn with king
												delete board[row][col];
												board[row][col] = kingPiece;

											}

											// Check for win conditions
											// TODO: render an overlay with the player which won
											if (didWin(board, selectedPiece->getColor())) {
												std::cout << "Game Over\n";
												gameOver(); 
											}

											//state reset
											selectedPiece->deselectPiece();
											selectedPiece = nullptr;
											selectedCol = -1;
											selectedRow = -1;
											currentState = pieceSelection;



											std::cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

											// now switch turns
											currentPlayer = sf::Color::Red;
											std::cout << "Turn switched to Red\n";
										}
										else
										{
											std::cout << "Cannot capture piece here\n";
										}

									}
									else if (rowDiff != colDiff)
									{
										std::cout << "Make sure to only move diagonally\n";
									}
									else
									{
										cout << "you cannot move that far\n";
									}
								}
							}
						}

						/*if (didWin(board, board[row][col]->getColor())) {
							std::cout << "Game Over\n";
							gameOver();
						}*/




						

						//if (rowDiff == 1 && colDiff == 1)
						//{
						//	

						//	// validating move direction for pawns here
						//	if (selectedPiece->getColor() == sf::Color::White && row < selectedRow) {
						//		std::cout << "White can only move down\n";
						//	}
						//	else if (selectedPiece->getColor() == sf::Color::Red && row > selectedRow) {
						//		std::cout << "Red can only move up\n";
						//	}
						//	else {

						//		// piece movement
						//		selectedPiece->setPosition(centerX - 50, centerY - 50); // controls visual repersentation
						//		board[row][col] = selectedPiece;
						//		board[selectedRow][selectedCol] = nullptr;
						//		// We want to continuously check if king promotion is possible
						//		if ((selectedPiece->getColor() == sf::Color::White && row == 7) || (selectedPiece->getColor() == sf::Color::Red && row == 0))
						//		{
						//			// King piece creation here
						//			King* kingPiece = new King(selectedPiece->getColor(), centerX
						//				- 50, centerY - 50);

						//			// replacing pawn with king
						//			delete board[row][col];
						//			board[row][col] = kingPiece;

						//		}

						//		// Check for win conditions
						//		// TODO: render an overlay with the player which won
						//		if (didWin(board, board[row][col]->getColor())) {
						//			std::cout << "Game Over\n";
						//			gameOver();

						//		}

						//		// state reset
						//		selectedPiece = nullptr;
						//		selectedCol = -1;
						//		selectedRow = -1;
						//		currentState = pieceSelection;

						//		board[row][col]->deselectPiece();

						//		std::cout << "moved piece to: (" << col << "," << row << ")\n" << std::endl;




						//		// now switch turns
						//		if (currentPlayer == sf::Color::White) {
						//			currentPlayer = sf::Color::Red;
						//			std::cout << "Turn switched to Red\n";
						//			if (didWin(board, board[row][col]->getColor())) {
						//				std::cout << "Game Over\n";
						//				gameOver();

						//			}
						//		}
						//		else {
						//			currentPlayer = sf::Color::White;
						//			std::cout << "Turn switched to White\n";
						//			if (didWin(board, board[row][col]->getColor())) {
						//				std::cout << "Game Over\n";
						//				gameOver();

						//			}
						//		}
						//	}
						//}

						//// Piece-taking
						//else if (rowDiff == 2 && colDiff == 2) {
						//	int capturedRow = selectedRow + (row - selectedRow) / 2;
						//	int capturedCol = selectedCol + (col - selectedCol) / 2;

						//	if (board[capturedRow][capturedCol] != nullptr &&
						//		board[capturedRow][capturedCol]->getColor() != selectedPiece->getColor()) {

						//		selectedPiece->setPosition(centerX - 50, centerY - 50);
						//		board[row][col] = selectedPiece;
						//		board[selectedRow][selectedCol] = nullptr;
						//		delete board[capturedRow][capturedCol];
						//		board[capturedRow][capturedCol] = nullptr;

						//		selectedPiece = nullptr;
						//		selectedCol = -1;
						//		selectedRow = -1;
						//		currentState = pieceSelection;

						//		board[row][col]->deselectPiece();

						//		std::cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

						//		// now switch turns
						//		if (currentPlayer == sf::Color::White) {
						//			currentPlayer = sf::Color::Red;
						//			std::cout << "Turn switched to Red\n";
						//			if (didWin(board, board[row][col]->getColor())) {
						//				std::cout << "Game Over\n";
						//				gameOver();
						//			}
						//		}
						//		else {
						//			currentPlayer = sf::Color::White;
						//			std::cout << "Turn switched to White\n";
						//			if (didWin(board, board[row][col]->getColor())) {
						//				std::cout << "Game Over\n";
						//				gameOver();
						//			}
						//		}
						//	}


						//	else {
						//		std::cout << "Cannot capture piece here\n";
						//	}
						//}

						//else {
						//	std::cout << "Make sure to only move diagonally\n";
						//}
					}
					
					


					else if (currentState == pieceMove && board[row][col] != nullptr)
					{

						std::cout << "Cannot move here; tile (" << col << "," << row << ") is occupied.\n";
					}
				}

			}


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

		// This loop renders the pieces in the window
		// Piece rendering using the above 2 piece instantiation loops
		for (int row = 0; row < 8; ++row)
		{
			for (int col = 0; col < 8; ++col)
			{
				if (board[row][col] != nullptr) // Check if a piece exists at this position
				{
					window.draw(board[row][col]->getShape()); // Draw the piece
					window.draw(board[row][col]->getKingMarker()); // This function is called for all types of pieces, including pawns. A pawn will return an empty shape
				}
			}
		}

		window.display();
	}

	return;
}