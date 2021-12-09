#pragma once

#include <vector>
#include <string>

#include "../Headers/Message.hpp"

const int BOARD_SIZE = 3;
const int TIE_INDICATOR = 69;
const std::string BOTTOM_AXIS = "-----1----------2----------3-----";

enum Marker {
	BLANK, X, O
};
 
class GameBoard {
public:
	GameBoard();
	void print();
	int getValueAtPosition(int, int) const;
	void setValueAtPosition(int, int, int);
	int getSize() const { return board.size(); }
	int checkVictory();
	std::vector<int> board;
	std::vector<Move> humanMoves;
	std::vector<Move> computerMoves;
};
