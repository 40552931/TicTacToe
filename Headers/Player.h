#pragma once

#include "GameBoard.h"
#include "ServerResponse.h"

#include <tuple>

class Player {
public:
	virtual Move getMove(GameBoard&, int, int) = 0;
	virtual void performMove(GameBoard&) = 0;
	virtual void initialize(int) = 0;
	void setMarkers(int marker);
	int getMarker() { return _marker; };
	int getOtherPlayerMarker() { return _otherPlayer; };
	std::string getName() { return _name; };
	void setName(std::string name) { _name = name; };
	std::tuple<int, int> nextMove;
private:
	std::string _name;
	int _marker;
	int _otherPlayer;
};
