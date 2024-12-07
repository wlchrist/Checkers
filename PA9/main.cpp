#pragma once
#include "Game.hpp"
#include "testCases.h"
#include <Windows.h>

int main()
{
	testCases test;
	test.checkGameOver();
	test.checkMovement();
	test.checkValidCord();
	test.checkKing();
	test.checkTurnOrder();
	std::cout << "all tests complete" << endl;
	Sleep(1200);
	std::cout << "3" << endl;
	Sleep(1200);
	std::cout << "2" << endl;
	Sleep(1200);
	std::cout << "1" << endl;
	system("cls");


	Game game;
	game.runGame();

	return 0;
}