#include "../Headers/GameController.h"
#include "../Headers/ServerResponse.h"
#include <iostream>
#include <vector>
using namespace std;

class CheckVictory_Test {
public:
	GameController game;
	int wins = 0;
	int attempts = 0;

	void init() {
		game.beginGame();
	}

	int test(int move1x, int move1y, int move2x, int move2y, int move3x, int move3y) {
		attempts++;
		game.gameBoard.setValueAtPosition(move1x, move1y, 1);
		game.gameBoard.setValueAtPosition(move2x, move2y, 1);
		game.gameBoard.setValueAtPosition(move3x, move3y, 1);
		if (game.checkVictory()) {
			cout << "[*] Winner detected from moves " << move1x << "," << move1y << "     " << move2x << "," << move2y << "     " << move3x << "," << move3y << "     " << endl;
			wins++;
			game.gameBoard.clear();
			return 1;
		} else {
			cout << "[*] No winner detected from moves " << move1x << "," << move1y << "     " << move2x << "," << move2y << "     " << move3x << "," << move3y << "     " << endl;
			return 0;
		}
	}

	void showSummary() {
		cout << "[*] Out of " << attempts << " attempts, there were " << wins << " wins detected. There should be 8" << endl;;
	}
};


int main() {
	CheckVictory_Test cv;
	cv.init();
	// Left to right diagonal
	cv.test(0, 0, 1, 1, 2, 2);
	// Right to left diagonal
	cv.test(2, 0, 0, 2, 1, 1);
	// Left column
	cv.test(0, 0, 0, 1, 0, 2);
	// Middle column
	cv.test(1, 0, 1, 1, 1, 2);
	// Right column
	cv.test(2, 0, 2, 1, 2, 2);
	// Bottom row
	cv.test(0, 0, 1, 0, 2, 0);
	// Middle row
	cv.test(0, 1, 1, 1, 2, 1);
	// Top row
	cv.test(0, 2, 1, 2, 2, 2);

	// Some other garbage
	cv.test(0, 1, 2, 1, 2, 0);
	cv.test(0, 0, 0, 1, 2, 1);

	cv.showSummary();
}