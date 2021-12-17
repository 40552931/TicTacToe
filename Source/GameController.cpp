#include "../Headers/GameController.h"
#include "../Headers/GameBoard.h"

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <math.h>

using namespace std;

int GameController::initializePlayers(int playerMarkerChoice) {
	int playerMarker = playerMarkerChoice;
	// get opposite of player marker
	int computerMarker = playerMarker == X ? O : X;
	currentGameState = ACTIVE;
	humanPlayer.initialize(playerMarker);
	computerPlayer.initialize(computerMarker);
	int tossWin = decideFirstPlayer(playerMarker, computerMarker);
	return tossWin;
}

void GameController::setCurrentPlayer(int currentPlayerMarker) {
	// Assign currentPlayer to whoever won the toss, also output message because if AI goes first, it takes a while.. 
	currentPlayerMarker == X ? (currentPlayer = &humanPlayer) : ( currentPlayer = &computerPlayer);
}

int GameController::decideFirstPlayer(int playerMarker, int computerMarker) {
	// Get random number between 1 and 2 (player marker indicator);
	this_thread::sleep_for(chrono::milliseconds(200));
	random_device randomDevice;
	mt19937 gen(randomDevice());
	uniform_int_distribution<> distr(1, 2);
	int result = distr(gen);
	setCurrentPlayer(result);
	if (currentPlayer->getMarker() == computerMarker)
		computerGo();
	return result;
}

bool GameController::canMoveAtPosition(int x, int y) {
	return (gameBoard.getValueAtPosition(x-1, y-1) == 0);
}

void GameController::computerGo() {
	currentPlayer->performMove(gameBoard);
	switchPlayerTurn();
	return;
}

void GameController::playerGo() {
	currentPlayer->performMove(gameBoard);
	switchPlayerTurn();
	computerGo();
}

void GameController::beginGame() {
	gameBoard.board.resize(pow(BOARD_SIZE, 2));
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