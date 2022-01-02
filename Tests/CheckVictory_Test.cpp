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

	int testWin(int move1x, int move1y, int move2x, int move2y, int move3x, int move3y) {
		attempts++;
		game.gameBoard.setValueAtPosition(move1x, move1y, 1);
		game.gameBoard.setValueAtPosition(move2x, move2y, 1);
		game.gameBoard.setValueAtPosition(move3x, move3y, 1);
		if (game.gameBoard.checkVictory()) {
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

	void testWins() {
		// Left to right diagonal
		testWin(0, 0, 1, 1, 2, 2);
		// Right to left diagonal
		testWin(2, 0, 0, 2, 1, 1);
		// Left column
		testWin(0, 0, 0, 1, 0, 2);
		// Middle column
		testWin(1, 0, 1, 1, 1, 2);
		// Right column
		testWin(2, 0, 2, 1, 2, 2);
		// Bottom row
		testWin(0, 0, 1, 0, 2, 0);
		// Middle row
		testWin(0, 1, 1, 1, 2, 1);
		// Top row
		testWin(0, 2, 1, 2, 2, 2);

		// Some other garbage
		testWin(0, 1, 2, 1, 2, 0);
		testWin(0, 0, 0, 1, 2, 1);
		showSummary();
	}

	void testDraw() {
		game.gameBoard.setValueAtPosition(0, 0, 1);
		game.gameBoard.setValueAtPosition(0, 1, 1);
		game.gameBoard.setValueAtPosition(0, 2, 2);
		game.gameBoard.setValueAtPosition(1, 1, 2);
		game.gameBoard.setValueAtPosition(1, 0, 2);
		game.gameBoard.setValueAtPosition(1, 2, 1);
		game.gameBoard.setValueAtPosition(2, 0, 1);
		game.gameBoard.setValueAtPosition(2, 2, 1);
		game.gameBoard.setValueAtPosition(2, 1, 2);
		game.gameBoard.print();
		int winner = game.gameBoard.checkVictory();
		if (winner == 3)
			cout << "Draw detected - succuess" << endl;
	}
};


int main() {
	CheckVictory_Test cv;
	cv.init();
	//cv.testWins();
	cv.testDraw();
}