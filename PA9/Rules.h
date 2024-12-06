#pragma once
#include "SFML/Graphics.hpp"
#include "Piece.h"

// Header file for helper functions pertaining to the rules of the game

// Checking if player has won
inline bool didWin(Piece* board[8][8], sf::Color playerColor) {

	sf::Color enemyColor = (playerColor == sf::Color::White) ? sf::Color::Red : sf::Color::White;
	bool enemyHasPieces = false;
	bool enemyCanMove = false;

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (board[row][col] != nullptr && board[row][col]->getColor() == enemyColor) {
				enemyHasPieces = true;
				int moveDirection = (enemyColor == sf::Color::White) ? 1 : -1;

				for (int colDiff : {-1, 1}) {
					int newRow = row + moveDirection;
					int newCol = col + colDiff;

					if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
						if (board[newRow][newCol] == nullptr) {
							enemyCanMove = true;
							return false;

						}
					}
				}

				for (int colDiff : {-2, 2}) {
					for (int rowDiff : {-2, 2}) {
						int newRow = row + rowDiff;
						int newCol = col + colDiff;

						if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
							if (board[newRow][newCol] == nullptr) {
								int midRow = row + rowDiff / 2;
								int midCol = col + colDiff / 2;
								if (board[midRow][midCol] != nullptr && board[midRow][midCol]->getColor() != enemyColor) {
									enemyCanMove = true;
									return false;
								}
							}
						}
					}
				}

			}
		}
	}

	return enemyHasPieces == false || enemyCanMove == false;

}

// Turn management
inline bool isValidTurn(Piece* piece, sf::Color currentPlayer) {
	if (piece == nullptr) {
		return false;
	}
	if (piece->getColor() == currentPlayer) {
		return true;
	}
	return false;
}