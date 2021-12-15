#pragma once

#include "GameController.h"
#include "Client.h"
#include "ClientRequest.h"

class ClientApp {
public:
	ClientApp();
	int playerMarker;
	void onMessageReceive(std::string);
	void beginConnection();
	void beginMarkerChoice();
	void serializeAndSend(ClientRequest);
	void endGameSequence(int);
	ServerResponse deserializeServerResponse(std::string);
	void beginMoveInputSequence();
	void askToPlay();
	Client client;
	GameController game;
};