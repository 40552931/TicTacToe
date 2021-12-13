#include "../Headers/HumanPlayer.h"
#include "../Headers/ComputerPlayer.h"
#include "../Headers/ServerResponse.h"

#include <iostream>
#include <vector>
#include <string>

<<<<<<< HEAD
=======
#include "../Headers/HumanPlayer.h"
#include "../Headers/ComputerPlayer.h"
#include "../Headers/Message.h"

>>>>>>> 9a93491a3ddf58a2ad0c7eebd8a77454df42e331
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
