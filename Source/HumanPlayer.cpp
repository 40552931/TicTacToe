#include <iostream>
#include <vector>
#include <string>

#include "../Headers/HumanPlayer.h"
#include "../Headers/ComputerPlayer.h"
#include "../Headers/Message.hpp"

using namespace std;

Move HumanPlayer::getMove(GameBoard&, int, int) {
	int x, y;
	x = get<0>(nextMove);
	y = get<1>(nextMove);
	Move move(x, y);
	return move;
}

void HumanPlayer::performMove(GameBoard& board) {
	Move playerMove = getMove(board, getMarker());
	cout << "[*] Player moving to (" << get<0>(playerMove.position) << ", " << get<1>(playerMove.position) << ")" << endl;
	board.humanMoves.push_back(playerMove);
	int x, y;
	tie(x, y) = playerMove.position;
	board.setValueAtPosition(x - 1, y - 1, getMarker());
}

void HumanPlayer::initialize(int humanPlayerMarker) {
	setMarkers(humanPlayerMarker);
	setName("Human");
}
