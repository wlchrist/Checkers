#include "testCases.h"

void testCases::checkGameOver()
{
	sf::Color Player1 = sf::Color::White;

	sf::Color Player2 = sf::Color::Red;

	bool playerHasPieces = true;
	bool playerCanMove = false;

		
	if (playerCanMove != true || playerHasPieces != true )
	{	
	}
	else
	{
		std::cout << "Error in did win";
		exit(11);
	}

	 playerHasPieces = false;
	 playerCanMove = true;


	if (!playerCanMove || !playerHasPieces)
	{	
	}
	else
	{
		std::cout << "Error in did win";
		exit(11);
	}

	return;
}

void testCases::checkMovement()
{
	Piece* Board[8][8];

	Game gameInstance;
	Piece* selectedPiece = new Pawn(sf::Color::White, 100, 100);
	sf::Color CurrentPlayer = sf::Color::White;
	int selctedRow = 2, selectedcol = 2;
	int row = 3, col = 3;
	float centerx = 150.0f, centerY = 150.0f;
	int rowDiff = row - selctedRow, coldiff = col - selectedcol;

	gameInstance.movePiece(rowDiff, coldiff, selectedPiece, centerx, centerY, row, col, selctedRow, selectedcol, CurrentPlayer);

	if (selectedPiece == nullptr)
	{
		std::cout << "movment succsessful" << endl;
	}
	else
	{
		std::cout << "error in movePiece (movment)" << endl;
		exit(22);
	}

	
	selectedPiece = new Pawn(sf::Color::White, 100, 100);
	CurrentPlayer = sf::Color::White;
	selctedRow = 2, selectedcol = 2;
	row = 4, col = 4;
	centerx = 150.0f, centerY = 150.0f;
	rowDiff = row - selctedRow, coldiff = col - selectedcol;
	
	gameInstance.movePiece(rowDiff, coldiff, selectedPiece, centerx, centerY, row, col, selctedRow, selectedcol, CurrentPlayer);
	
	if (selectedPiece == nullptr)
	{
		std::cout << "error in movePiece (invalid move)" << endl;
		exit(22);
	}
	else
	{
		std::cout << "movment succsessfuly blocked" << endl;
	}

}

void testCases::checkValidCord()
{
	Piece* Board[8][8];

	Game gameInstance;
	Piece* selectedPiece = new Pawn(sf::Color::White, 100, 100);
	sf::Color CurrentPlayer = sf::Color::White;
	int selctedRow = 200, selectedcol = 44;
	int row = 399, col = 11;
	float centerx = 150.0f, centerY = 150.0f;
	int rowDiff = row - selctedRow, coldiff = col - selectedcol;

	gameInstance.movePiece(rowDiff, coldiff, selectedPiece, centerx, centerY, row, col, selctedRow, selectedcol, CurrentPlayer);

	if (selectedPiece == nullptr)
	{
		std::cout << "error in movePiece (bounds)" << endl;
		exit(33);
	}
	else
	{
		std::cout << "out of bounds movment succsessfully blocked" << endl;
		
	}


	

	
	


}

void testCases::checkKing()
{
	Piece* Piece1 = new Pawn(sf::Color::White, 100, 100);

	Piece* Piece2 = new King(sf::Color::White, 100, 100);

	if (Piece1->getPieceType() == "king")
	{
		std::cout << "error in Piece detection (pawn seen as king)" << endl;
		exit(44);
	}
	else
	{
		std::cout << "Piece type validation succsessful" << endl;
	}

	if (Piece2->getPieceType() == "king")
	{
		std::cout << "Piece type validation succsessful" << endl;
	}
	else
	{
		std::cout << "error in Piece detection (king not recignized)" << endl;
		exit(44);
	}
}

void testCases::checkTurnOrder()
{

	Piece* piece = new Pawn(sf::Color::White, 100, 100);
	sf::Color currentPlayer = sf::Color::White;
	

	if (isValidTurn(piece, currentPlayer))
	{
		std::cout << "turn successfully validated" << endl;
	}
	else if (!isValidTurn(piece, currentPlayer))
	{

		std::cout << "Error in did player turn";
		exit(55);
	}

	piece = new Pawn(sf::Color::Red, 100, 100);
	currentPlayer = sf::Color::White;


	if (isValidTurn(piece, currentPlayer))
	{

		std::cout << "Error in player turn";
		exit(55);
	}
	else if (!isValidTurn(piece, currentPlayer))
	{
		std::cout << "turn successfully validated" << endl;
	}


}


