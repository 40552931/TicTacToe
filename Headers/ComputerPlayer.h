#pragma once

#include "Player.h"

#include <tuple>

class ComputerPlayer : public Player {
public:
	// Override functions 
	Move getMove(GameBoard&, int, int = 0) override;
	void performMove(GameBoard&) override;
	void initialize(int aiPlayerMarker) override;
};
