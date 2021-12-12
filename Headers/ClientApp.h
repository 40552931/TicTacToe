#pragma once

#include <iostream>

#include "GameController.h"
#include "Client.h"
#include "Message.hpp"

class ClientApp {
public:
	ClientApp();
	void onMessageReceive(std::string);
	void beginConnection();
	void beginMarkerChoice();
	void serializeAndSend(ClientRequest);
	void beginMoveInputSequence();
	void askToPlay();
	Client client;
	GameController game;
};