#include "../Headers/GameController.h"
#include "../Headers/GameBoard.h"

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <math.h>

using namespace std;

int GameController::checkVictory() {
	// maybe re-write this... bit clunky
	bool hasWon;
	int winnerMarker;
	//row
	for (int y = 0; y < 3; y++)
	{
		winnerMarker = gameBoard.getValueAtPosition(0, y);
		if (winnerMarker != BLANK) {
			hasWon = true;
			for (int x = 0; x < 3; x++)
			{
				if (gameBoard.getValueAtPosition(x, y) != winnerMarker) {
					hasWon = false;
					break;
				}
			}
			if (hasWon) {
				return winnerMarker;
			}
		}
	}
	// col
	for (int x = 0; x < 3; x++)
	{
		winnerMarker = gameBoard.getValueAtPosition(x, 0);
		if (winnerMarker != BLANK) {
			hasWon = true;
			for (int y = 0; y < 3; y++)
			{
				if (gameBoard.getValueAtPosition(x, y) != winnerMarker) {
					hasWon = false;
					break;
				}
			}
			if (hasWon) {
				return winnerMarker;
			}
		}
	}
	// diag
	winnerMarker = gameBoard.getValueAtPosition(0, 0);
	if (winnerMarker != BLANK) {
		hasWon = true;
		for (int xy = 0; xy < 3; xy++) {
			if (gameBoard.getValueAtPosition(xy, xy) != winnerMarker) {
				hasWon = false;
				break;
			}
		}
		if (hasWon) {
			return winnerMarker;
		}
	}
	// other diag
	winnerMarker = gameBoard.getValueAtPosition(BOARD_SIZE - 1, 0);
	if (winnerMarker != BLANK) {
		hasWon = true;
		for (int xy = 0; xy < BOARD_SIZE; xy++) {
			if (gameBoard.getValueAtPosition(BOARD_SIZE - xy - 1, xy) != winnerMarker) {
				hasWon = false;
				break;
			}
		}
		if (hasWon) {
			return winnerMarker;
		}
	}

	for (size_t x = 0; x < 3; x++) {
		for (size_t y = 0; y < 3; y++)
		{
			if (gameBoard.getValueAtPosition(x, y) == BLANK) return BLANK;
		}
	}
	// If we get here, every spot was filled, so return tie
	return TIE_INDICATOR;
}

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