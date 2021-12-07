#include <iostream>
#include <string>

#include "../Headers/GameController.h"

using namespace std;

void GameController::endGame(int winner) {
	cout << "-= GAME OVER =-" << endl;
	cout << winner << " WINS!" << endl;
}

void GameController::beginGame() {
	gameBoard.board.resize(9); // MAGIC NUMBER
	gameBoard.checkVictory();
	currentGameState = ACTIVE;
	humanPlayer.initialize(X); // HUMAN PLAYER - NEED TO ADD TOSS
	currentPlayer = &humanPlayer;
	computerPlayer.initialize(O);
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
