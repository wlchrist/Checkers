#pragma once
#include "Pawn.h"
#include "King.h"
#include "StateMachine.h"
#include "Rules.h"
#include "GameOverComponent.h"
#include "Server.h"
#include "Client.h"

class Game
{
private:
	sf::RenderWindow window;
	gameState currentState;
	Piece* board[8][8]; // board instantiation, not to be confused with rendering
	sf::Event event;

public:
	Game();

	~Game();
	void initializeBoard();
	void runGame(); //runs the game
	std::string getBoardState();
	void renderBoard();
	void renderPieces();

	bool isMouseClickValid(sf::Vector2i& mousePosition); //checks to see that all left mouse clicks are within the bounds of the window.

	void runTurn(int& mouseX, int& mouseY, sf::Color& currentPlayer, Piece*& selectedPiece, int& selectedRow, int& selectedCol); //run player turn

	void getPiece(int& row, int& col, sf::Color& currentPlayer, Piece*& selectedPiece, int& selectedRow, int& selectedCol);

	void movePiece(int rowDiff, int colDiff, Piece*& selectedPiece, float centerX, float centerY, int row, int col, int selectedRow, int selectedCol, sf::Color& currentPlayer);
};

