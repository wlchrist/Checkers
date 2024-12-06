#include "Game.hpp"

Game::Game() //ignore this warning. We can't "initialize" 'event'
{
	window.create(sf::VideoMode(1600, 1600), "Checkers");
	currentState = pieceSelection;

	//first initialize all cells in the board to nullptrs. 
	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; y++)
		{
			board[y][x] = nullptr;
		}
	}
	// P1 piece placement
	for (int row = 0; row < 2; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{

			if ((row + col) % 2 == 1)
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
}


Game::~Game()
{
}

void Game::renderBoard()
{
	sf::RectangleShape rect1(sf::Vector2f(200.f, 200.f));
	sf::RectangleShape rect2(sf::Vector2f(200.f, 200.f));
	rect1.setFillColor(sf::Color::White);
	rect2.setFillColor(sf::Color::Black);

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
}

void Game::renderPieces()
{
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (board[row][col] != nullptr) // Check if a piece exists at this position
			{
				window.draw(board[row][col]->getShape()); // Draw the piece
				window.draw(board[row][col]->getKingMarker()); // This function is called for all types of pieces, including pawns. A pawn will just return an empty shape
			}
		}
	}
}

bool Game::isMouseClickValid(sf::Vector2i& mousePosition)
{
	return (mousePosition.x >= 0 &&
		mousePosition.x <= 1600 &&
		mousePosition.y >= 0 &&
		mousePosition.x <= 1600);
}

void Game::runGame()
{
	sf::Color currentPlayer = sf::Color::Red;
	Piece* selectedPiece = nullptr;
	int selectedRow = -1, selectedCol = -1;

	while (window.isOpen())
	{
		const int BOARD_SIZE = 8;
		int mouseX = -1;
		int mouseY = -1;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				//close the game window
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) // checks for left click
			{
				//player is attempting to move a piece
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);// gets mouse postition in vector form

				//check that the mouse click is within the window
				if (isMouseClickValid(mousePosition) == true)
				{
					mouseX = mousePosition.x;// sets x mouse coord
					mouseY = mousePosition.y;// sets y mouse coord

					runTurn(mouseX, mouseY, currentPlayer, selectedPiece, selectedRow, selectedCol);
				}
			}
			else if (event.type == sf::Event::KeyPressed && currentState == pieceMove)
			{
				//person is attempting to deselect a piece
				if (event.key.code == 36)
				{
					selectedCol = -1;
					selectedRow = -1;
					currentState = pieceSelection;
					cout << "Piece deselected.\n";
					selectedPiece->deselectPiece();
				}
			}
		}
		window.clear();

		renderBoard();
		renderPieces();

		window.display();
	}
}

void Game::runTurn(int& mouseX, int& mouseY, sf::Color& currentPlayer, Piece*& selectedPiece, int& selectedRow, int& selectedCol)
{
	float tileSizeX = window.getSize().x / 8.0;// get current tile size y
	float tileSizeY = window.getSize().y / 8.0;// get current tile size x

	int col = mouseX / tileSizeX;// divide X click coords by curent X tile size to accurelty get array coords
	int row = mouseY / tileSizeY;// divide Y click coords by curent Y tile size to accurelty get array coords

	float colAC = static_cast<float>(col);
	float rowAC = static_cast<float>(row);

	float centerX = colAC * tileSizeX + (tileSizeX - 100.0) / 2;
	float centerY = rowAC * tileSizeY + (tileSizeY - 100.0) / 2;
	// 1-4 are attempts to constrain piece placment for more accurate visuals


	// Piece selection code block
	if (currentState == pieceSelection && board[row][col] != NULL)
	{
		getPiece(row, col, currentPlayer, selectedPiece, selectedRow, selectedCol);
	}
	else if (currentState == pieceMove && board[row][col] == nullptr /*tile they selected to move to is empty*/)
	{
		int rowDiff = abs(row - selectedRow);
		int colDiff = abs(col - selectedCol);

		//Attempt to move the piece
		movePiece(rowDiff, colDiff, selectedPiece, centerX, centerY, row, col, selectedRow, selectedCol, currentPlayer);
	}
	else if (currentState == pieceMove && board[row][col] != nullptr)
	{

		cout << "Cannot move here; tile (" << col << "," << row << ") is occupied.\n";
	}
}

void Game::getPiece(int& row, int& col, sf::Color& currentPlayer, Piece*& selectedPiece, int& selectedRow, int& selectedCol)
{
	// Validates if whose turn it is using function from Rules.h
	if (!isValidTurn(board[row][col], currentPlayer)) {
		if (currentPlayer == sf::Color::White) {
			cout << "White must move\n";

		}
		else {
			cout << "Red must move\n";
		}
	}
	else {
		// Set piece as selected
		board[row][col]->selectPiece();

		selectedPiece = board[row][col];
		selectedCol = col;
		selectedRow = row;
		currentState = pieceMove;
		cout << "Selected piece at: (" << col << "," << row << ")\n" << endl;
	}
}

void Game::movePiece(int rowDiff, int colDiff, Piece*& selectedPiece, float centerX, float centerY, int row, int col, int selectedRow, int selectedCol, sf::Color& currentPlayer)
{
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
					cout << "Game Over\n";
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
				cout << "Turn switched to White\n";

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
						cout << "Game Over\n";
						gameOver();
					}

					//state reset
					selectedPiece->deselectPiece();
					selectedPiece = nullptr;
					selectedCol = -1;
					selectedRow = -1;
					currentState = pieceSelection;

					cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

					// now switch turns
					currentPlayer = sf::Color::White;
					cout << "Turn switched to White\n";
				}
				else
				{
					cout << "Cannot capture piece here\n";
				}
			}
			else if (rowDiff != colDiff)
			{
				cout << "Make sure to only move diagonally\n";
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
				cout << "Red can only move up\n";
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
						cout << "Game Over\n";
						gameOver();
					}

					// state reset
					selectedPiece->deselectPiece();
					selectedPiece = nullptr;
					selectedCol = -1;
					selectedRow = -1;
					currentState = pieceSelection;

					cout << "moved piece to: (" << col << "," << row << ")\n" << endl;

					// now switch turns
					currentPlayer = sf::Color::White;
					cout << "Turn switched to White\n";


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
							cout << "Game Over\n";
							gameOver();
						}

						//state reset
						selectedPiece->deselectPiece();
						selectedPiece = nullptr;
						selectedCol = -1;
						selectedRow = -1;
						currentState = pieceSelection;



						cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

						// now switch turns
						currentPlayer = sf::Color::White;
						cout << "Turn switched to White\n";
					}
					else
					{
						cout << "Cannot capture piece here\n";
					}

				}
				else if (rowDiff != colDiff)
				{
					cout << "Make sure to only move diagonally\n";
				}
				else
				{
					cout << "you cannot move that far\n";
				}
			}
		}
	}

	//this code is very similar to that of a red piece, just with a few sign changes and different value checks
	else if (selectedPiece->getColor() == sf::Color::White)
	{
		//White
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
					cout << "Game Over\n";
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
				cout << "Turn switched to Red\n";

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
						cout << "Game Over\n";
						gameOver();
					}

					//state reset
					selectedPiece->deselectPiece();
					selectedPiece = nullptr;
					selectedCol = -1;
					selectedRow = -1;
					currentState = pieceSelection;



					cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

					// now switch turns
					currentPlayer = sf::Color::Red;
					cout << "Turn switched to Red\n";

				}
				else
				{
					cout << "Cannot capture piece here\n";
				}
			}
			else if (rowDiff != colDiff)
			{
				cout << "Make sure to only move diagonally\n";
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
				cout << "White can only move down\n";
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
						cout << "Game Over\n";
						gameOver();
					}

					// state reset
					selectedPiece->deselectPiece();
					selectedPiece = nullptr;
					selectedCol = -1;
					selectedRow = -1;
					currentState = pieceSelection;

					cout << "moved piece to: (" << col << "," << row << ")\n" << endl;

					// now switch turns
					currentPlayer = sf::Color::Red;
					cout << "Turn switched to Red\n";


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
							cout << "Game Over\n";
							gameOver();
						}

						//state reset
						selectedPiece->deselectPiece();
						selectedPiece = nullptr;
						selectedCol = -1;
						selectedRow = -1;
						currentState = pieceSelection;



						cout << "Captured piece at (" << capturedRow << "," << capturedCol << ")\n";

						// now switch turns
						currentPlayer = sf::Color::Red;
						cout << "Turn switched to Red\n";
					}
					else
					{
						cout << "Cannot capture piece here\n";
					}

				}
				else if (rowDiff != colDiff)
				{
					cout << "Make sure to only move diagonally\n";
				}
				else
				{
					cout << "you cannot move that far\n";
				}
			}
		}
	}
}