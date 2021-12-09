#pragma once

#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "Player.h"
#include "GameBoard.h"

enum State { ACTIVE, QUIT };

class GameController {
public:
	void beginGame();
	void initializePlayers(int);
	void decideFirstPlayer(int, int);
	void setCurrentPlayer(int);
	Player* getCurrentPlayer() {return currentPlayer; };
	//GameBoard* getGameBoard() {return gameBoard; };
	void switchPlayerTurn();
	void endGame(int);
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