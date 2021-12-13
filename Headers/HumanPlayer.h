#pragma once

#include "Player.h"
<<<<<<< HEAD
#include "ServerResponse.h"
=======

#include "../Headers/Message.h"
>>>>>>> 9a93491a3ddf58a2ad0c7eebd8a77454df42e331

#include <tuple>

class HumanPlayer : public Player {
public:
	Move getMove(GameBoard&, int, int = 0) override;
	void performMove(GameBoard&) override;
	void initialize(int humanPlayerMarker) override;
};
