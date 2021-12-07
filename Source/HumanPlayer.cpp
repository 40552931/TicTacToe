#include <iostream>

#include "../Headers/HumanPlayer.h"
#include "../Headers/ComputerPlayer.h"

using namespace std;

Move HumanPlayer::getMove(GameBoard& board, int, int) {
	bool canPlaceAtLocation = false;
	int x, y;
	do {
		cout << "Enter X: ";
		while (!(cin >> x)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Enter a number";
		}
		cout << "Enter Y: ";
		while (!(cin >> y)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Enter a number";
		}

		if (x < 1 || y < 1 || x > board.getSize() || y > board.getSize()) {
			printf("ERROR: Invalid X or Y!\n");
		}
		else if (board.getValueAtPosition(x - 1, y - 1) != 0) {
			printf("ERROR: That spot is taken!\n");
		}
		else {
			canPlaceAtLocation = true;
		}
	} while (!canPlaceAtLocation);
	Move move(x, y);
	return move;
}

void HumanPlayer::performMove(GameBoard& board) {
	Move playerMove = getMove(board, getMarker());
	int x, y;
	tie(x, y) = playerMove.position;
	board.setValueAtPosition(x - 1, y - 1, getMarker());
}

void HumanPlayer::initialize(int humanPlayerMarker) {
	setMarkers(humanPlayerMarker);
	setName("Human");
}
