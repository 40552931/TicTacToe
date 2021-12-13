#pragma once

#include "Player.h"
#include "ServerResponse.h"

#include <tuple>

class HumanPlayer : public Player {
public:
	Move getMove(GameBoard&, int, int = 0) override;
	void performMove(GameBoard&) override;
	void initialize(int humanPlayerMarker) override;
};
