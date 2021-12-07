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

void GameController::setCurrentPlayer(int currentPlayerMarker) {
	// Assign currentPlayer to whoever won the toss, also output message because if AI goes first, it takes a while.. 
	currentPlayerMarker == X ? (currentPlayer = &humanPlayer) : ( cout << "Computer must calculate all possible moves, please be patient\n", currentPlayer = &computerPlayer);
	std::cout << currentPlayer->getName() << " has won the toss.. they will go first!\n";
}

void GameController::decideFirstPlayer(int playerMarker, int computerMarker) {
	// Get random number between 1 and 2 (player marker indicator);
	cout << "Flipping coin to decide who goes first... \n";
	this_thread::sleep_for(chrono::milliseconds(400));
	random_device randomDevice;
	mt19937 gen(randomDevice());
	uniform_int_distribution<> distr(1, 2);
	setCurrentPlayer(distr(gen));
}

void GameController::beginGame() {
	// Square board size as 3^2 = 9 = number of spaces
	gameBoard.board.resize(pow(BOARD_SIZE, 2));
	int playerMarker = getPlayerMarkerChoice();
	// get opposite of player marker
	int computerMarker = playerMarker == X ? O : X;
	currentGameState = ACTIVE;
	humanPlayer.initialize(playerMarker);
	computerPlayer.initialize(computerMarker);
	decideFirstPlayer(playerMarker, computerMarker);
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