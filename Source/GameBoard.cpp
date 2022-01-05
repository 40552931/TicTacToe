#include "../Headers/GameBoard.h"

#include <string>
#include <iostream>

using namespace std;

GameBoard::GameBoard() {
	// Initialize the game board
	for (size_t x = 0; x < board.size(); x++)
	{
		for (size_t y = 0; y < board.size(); y++)
		{
			// Treat as 2d array, see board.getValueAtPosition below
			setValueAtPosition(x, y, BLANK);
		}
	}
}

void GameBoard::clear() {
	// clear the game board
	for (size_t x = 0; x < board.size(); x++)
	{
		for (size_t y = 0; y < board.size(); y++)
		{
			// Treat as 2d array, see board.getValueAtPosition below
			setValueAtPosition(x, y, BLANK);
		}
	}
}

int GameBoard::getValueAtPosition(int x, int y) const {
	// y * 3 + x allows the vector to be treated, and indexed
	// as a multidimensional array, which just makes thinking about
	// a game board so much easier (as cartesian co-ordinates)...
	// same for setValueAtPosition...
	return board[y * BOARD_SIZE + x];
}

void GameBoard::setValueAtPosition(int x, int y, int markerValue) {
	//cout << "Setting value at (" << x + 1 << "," << y + 1 << ")" << " by " << markerValue << endl;
	board[y * BOARD_SIZE + x] = markerValue;
}

string GameBoard::getBoardString() {
	string out = "\n";
	for (int y = 2; y >= 0; y--)
	{
		out += string("---------------------------------\n");
		out += string("|         |") += string("|         |") += string("|         |\n");
		for (int x = 0; x < 3; x++)
		{
			switch (getValueAtPosition(x, y)) {
			case 0:
				out += string("|    .    |");
				break;
			case 1:
				out += string("|    X    |");
				break;
			case 2:
				out += string("|    O    |");
				break;
			}
		}
		out += string("\n|         |") += string("|         |") += string("|         |\n");
	}
	out += BOTTOM_AXIS;
	return out;
}

void GameBoard::print() {
	for (int y = 2; y >= 0; y--)
	{
		cout << "---------------------------------" << endl;
		cout << "|         |" << "|         |" << "|         |" << endl;
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			switch (getValueAtPosition(x, y)) {
			case 0:
				cout << "|    .    |";
				break;
			case 1:
				cout << "|    X    |";
				break;
			case 2:
				cout << "|    O    |";
				break;
			}
		}
		cout << endl << "|         |" << "|         |" << "|         |" << endl;
	}
	cout << BOTTOM_AXIS << endl;
}

int GameBoard::checkVictory() {
	/*
	 * First check the rows for 3 in a row, then 
	 * columns, then check both diagonals
	 * return the integer indicative of the
	 * player who has won the game, if all spots
	 * are filled, then return a tie indicator (3).
	 * if no one won, and the game is not a tie,
	 * return 0
	*/
	bool hasWon;
	int winnerMarker;
	//row
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		winnerMarker = getValueAtPosition(0, y);
		if (winnerMarker != BLANK) {
			hasWon = true;
			for (int x = 0; x < BOARD_SIZE; x++)
			{
				if (getValueAtPosition(x, y) != winnerMarker) {
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
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		winnerMarker = getValueAtPosition(x, 0);
		if (winnerMarker != BLANK) {
			hasWon = true;
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				if (getValueAtPosition(x, y) != winnerMarker) {
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
	winnerMarker = getValueAtPosition(0, 0);
	if (winnerMarker != BLANK) {
		hasWon = true;
		for (int xy = 0; xy < BOARD_SIZE; xy++) {
			if (getValueAtPosition(xy, xy) != winnerMarker) {
				hasWon = false;
				break;
			}
		}
		if (hasWon) {
			return winnerMarker;
		}
	}
	// other diag
	winnerMarker = getValueAtPosition(BOARD_SIZE - 1, 0);
	if (winnerMarker != BLANK) {
		hasWon = true;
		for (int xy = 0; xy < BOARD_SIZE; xy++) {
			if (getValueAtPosition(BOARD_SIZE - xy - 1, xy) != winnerMarker) {
				hasWon = false;
				break;
			}
		}
		if (hasWon) {
			return winnerMarker;
		}
	}

	for (size_t x = 0; x < BOARD_SIZE; x++) {
		for (size_t y = 0; y < BOARD_SIZE; y++)
		{
			if (getValueAtPosition(x, y) == BLANK) return BLANK;
		}
	}
	// If we get here, every spot was filled, so return tie
	return TIE_INDICATOR;
}
