#pragma once

#include "GameController.h"
#include "Client.h"
<<<<<<< HEAD
#include "ServerResponse.h"
#include "ClientRequest.h"

#include <iostream>
=======
#include "Message.h"
>>>>>>> 9a93491a3ddf58a2ad0c7eebd8a77454df42e331

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