#include "../Headers/Player.h"

#include <iostream>
#include <tuple>

void Player::setMarkers(int marker) {
	_marker = marker;
	_otherPlayer = marker == X ? O : X;
}
