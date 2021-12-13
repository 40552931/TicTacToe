#pragma once

#include "GameController.h"
#include "Client.h"
#include "ServerResponse.h"
#include "ClientRequest.h"

#include <iostream>

class ClientApp {
public:
	ClientApp();
	void onMessageReceive(std::string);
	void beginConnection();
	void beginMarkerChoice();
	void serializeAndSend(ClientRequest);
	ServerResponse deserializeServerResponse(std::string);
	void beginMoveInputSequence();
	void askToPlay();
	Client client;
	GameController game;
};