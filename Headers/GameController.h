#pragma once

#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "GameBoard.h"

enum State { ACTIVE, QUIT };

class GameController {
public:
	void beginGame();
	int getPlayerMarkerChoice();
	void decideFirstPlayer(int, int);
	void setCurrentPlayer(int);
	void switchPlayerTurn();
	void endGame(int);
private:
	State currentGameState;
	GameBoard gameBoard;
	ComputerPlayer computerPlayer;
	HumanPlayer humanPlayer;
	Player* currentPlayer;
};