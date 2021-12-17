#include "../Headers/GameController.h"

#include <iostream>

/*
Used for playing the game
in the terminal, no client
or server interaction, just
input and output from stdout
and console.
*/

int main() {
	GameController game;
	game.beginGame();
	return 0;
}
