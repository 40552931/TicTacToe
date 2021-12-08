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
	void switchPlayerTurn();
	void endGame(int) ;
private:
	State currentGameState;
	GameBoard gameBoard;
	ComputerPlayer computerPlayer;
	HumanPlayer humanPlayer;
	Player* currentPlayer;
};