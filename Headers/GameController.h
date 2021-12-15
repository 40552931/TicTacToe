#pragma once

#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "Player.h"
#include "GameBoard.h"

enum State { ACTIVE, QUIT };

class GameController {
public:
	void beginGame();
	int initializePlayers(int);
	int decideFirstPlayer(int, int);
	void setCurrentPlayer(int);
	Player* getCurrentPlayer() {return currentPlayer; };
	void switchPlayerTurn();
	void playerGo();
	void computerGo();
	bool canMoveAtPosition(int x, int y);
	int checkVictory();
	GameBoard gameBoard;
private:
	State currentGameState;
	//GameBoard gameBoard;
	ComputerPlayer computerPlayer;
	HumanPlayer humanPlayer;
	Player* currentPlayer;
};