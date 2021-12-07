#include <iostream>
#include <tuple>

#include "../Headers/Player.h"

void Player::setMarkers(int marker) {
	_marker = marker;
	_otherPlayer = marker == X ? O : X;
}
