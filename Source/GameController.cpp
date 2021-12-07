#include <iostream>
#include <string>

#include "../Headers/GameController.h"

using namespace std;

void GameController::endGame(int winner) {
	cout << "-= GAME OVER =-" << endl;
	cout << winner << " WINS!" << endl;
}

int GameController::getPlayerMarkerChoice() {
	bool validChoice = false;
	int choice;
	do {
		cout << "Enter 1 for X, 2 for O: ";
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ERROR: Enter an integer!\n";
			cout << "Enter 1 for X, 2 for O: ";
		}
		if (choice != 1 && choice != 2)
			printf("ERROR: Enter 1 or 2! \n");
		else
			validChoice = true;
	} while (!validChoice);
	return choice;
}

void GameController::beginGame() {
	gameBoard.board.resize(9); // MAGIC NUMBER
	int playerMarker = getPlayerMarkerChoice();
	// get opposite of player marker
	int computerMarker = playerMarker == X ? O : X;
	currentGameState = ACTIVE;
	humanPlayer.initialize(playerMarker); // HUMAN PLAYER - NEED TO ADD TOSS
	currentPlayer = &humanPlayer;
	computerPlayer.initialize(computerMarker);
	//currentPlayerMarker = X; // player goes first
	while (currentGameState != QUIT) {
		gameBoard.print();
		currentPlayer->performMove(gameBoard);
		int winner = gameBoard.checkVictory();
		if (winner != BLANK)
			endGame(winner);
		else
			switchPlayerTurn();
	}
}

void GameController::switchPlayerTurn() {
	// If currently it's X, make it O, else X
	if (currentPlayer == &humanPlayer) {
		currentPlayer = &computerPlayer;
	}
	else {
		currentPlayer = &humanPlayer;
	}
}