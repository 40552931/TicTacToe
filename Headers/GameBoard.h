#pragma once

#include "../Headers/ServerResponse.h"

#include <vector>
#include <string>

const int BOARD_SIZE = 3;
const int TIE_INDICATOR = 3;
const std::string BOTTOM_AXIS = "-----1----------2----------3-----\n";

enum Marker {
	BLANK, X, O
};
 
class GameBoard {
public:
	GameBoard();
	void print();
	void clear();
	int getValueAtPosition(int, int) const;
	void setValueAtPosition(int, int, int);
	std::string getBoardString();
	int getSize() const { return board.size(); }
	int checkVictory();
	std::vector<int> board;
	std::vector<Move> humanMoves;
	std::vector<Move> computerMoves;
};
