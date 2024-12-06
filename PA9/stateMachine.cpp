#pragma once
#include "Piece.h"
#include "stateMachine.h"

void handleState(gameState& currentSate, Piece*& selectedPiece, int& selectedRow, int& selectedCol)
{
	if (currentSate == pieceSelection)
	{
		std::cout << "Select a piece!" << std::endl;
	}
	else if (currentSate == pieceMove)
	{
		std::cout << "Move the selected piece!" << std::endl;
	}
}
