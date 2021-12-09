#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>

#include "../Headers/GameController.h"

using namespace std;

void GameController::endGame(int winner) {
	cout << "-= GAME OVER =-" << endl;
	cout << winner << " WINS!" << endl;
}

void GameController::initializePlayers(int playerMarkerChoice) {
	int playerMarker = playerMarkerChoice;
	// get opposite of player marker
	int computerMarker = playerMarker == X ? O : X;
	currentGameState = ACTIVE;
	humanPlayer.initialize(playerMarker);
	computerPlayer.initialize(computerMarker);
	decideFirstPlayer(playerMarker, computerMarker);
	cout << "Player marker = " << playerMarker << " Computer marker = " << computerMarker << " Current player marker = " << currentPlayer->getMarker() << endl;
}

void GameController::setCurrentPlayer(int currentPlayerMarker) {
	// Assign currentPlayer to whoever won the toss, also output message because if AI goes first, it takes a while.. 
	currentPlayerMarker == X ? (currentPlayer = &humanPlayer) : ( cout << "Computer must calculate all possible moves, please be patient\n", currentPlayer = &computerPlayer);
	cout << currentPlayer->getName() << " has won the toss.. they will go first!" << endl;
}

void GameController::decideFirstPlayer(int playerMarker, int computerMarker) {
	// Get random number between 1 and 2 (player marker indicator);
	cout << "Flipping coin to decide who goes first... \n";
	this_thread::sleep_for(chrono::milliseconds(200));
	random_device randomDevice;
	mt19937 gen(randomDevice());
	uniform_int_distribution<> distr(1, 2);
	int result = distr(gen);
	setCurrentPlayer(result);
	cout << "reuslt: " << result << " computer marker = " << computerMarker <<endl;
	if (currentPlayer->getMarker() == computerMarker)
		computerGo();
}

void GameController::computerGo() {
	currentPlayer->performMove(gameBoard);
	gameBoard.print();
	switchPlayerTurn();
	return;
}

void GameController::playerGo() {
	currentPlayer->performMove(gameBoard);
	gameBoard.print();
	switchPlayerTurn();
	computerGo();
}

void GameController::beginGame() {
	cout << "gambegin called" << endl;
	gameBoard.board.resize(pow(BOARD_SIZE, 2));
	// Square board size as 3^2 = 9 = number of spaces
	/*gameBoard.board.resize(pow(BOARD_SIZE, 2));
	int count = 0;
	while (currentGameState != QUIT) {
		if (count == 10)
			break;
		gameBoard.print();
		currentPlayer->performMove(gameBoard);
		this_thread::sleep_for(chrono::milliseconds(800));
		int winner = gameBoard.checkVictory();
		if (winner != BLANK)
			endGame(winner);
		else
			switchPlayerTurn();
		count++;
	}*/
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