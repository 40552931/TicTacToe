#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind/bind.hpp>

#include "../Headers/Crypt.h"
#include "../Headers/Server.h"
#include "../Headers/ServerResponse.h"
#include "../Headers/ClientRequest.h"
#include "../Headers/GameController.h"
#include "../Headers/ServerApp.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>


using namespace std;

void ServerApp::serializeAndSend(Client* client, ServerResponse serverResponse) {
	std::stringstream messageStream;
	boost::archive::text_oarchive archive(messageStream);
	archive << serverResponse;
	string outboundData = Crypt::decryptEncrypt(messageStream.str());
	client->Send(outboundData);
	cout << "[*] " << serverResponse.message << " => [" << client->getRemoteAddress() << "]:" << client->getRemotePort() << endl;
}

ClientRequest ServerApp::deserializeClientRequest(Client* client, string message) {
	string decryptedMessage = Crypt::decryptEncrypt(message);
	istringstream stringStream(decryptedMessage);
	ClientRequest clientRequest;
	boost::archive::text_iarchive serializedText(stringStream);
	serializedText >> clientRequest;
	return clientRequest;
}

void ServerApp::begin() {
server.uponNewCon = [&](Client *client) {
	GameController game;
	cout << "[!] New client connected: [" << client->getRemoteAddress() << "]" << endl;
	client->onMessageReceived = [this, game, client](string message) mutable {
	ClientRequest clientRequest = deserializeClientRequest(client, message);
		cout << "[*] [" << client->getRemoteAddress() << "]:" << client->getRemotePort() << " => " << clientRequest.message << endl;
		if (clientRequest.message == "BEGIN_GAME_REQUEST") {
			game.beginGame();
			ServerResponse response(0, message="BEGIN_GAME_RESPONSE");
			serializeAndSend(client, response);
		}
		else if (clientRequest.message == "MARKER_CHOICE_REQUEST") {
			// Set up player markers - see begingame
			int playerMarker = clientRequest.markerChoice;
			int tossWin = game.initializePlayers(playerMarker);
			ServerResponse response(0, message="MARKER_CHOICE_RESPONSE", game.gameBoard.getBoardString(), game.getCurrentPlayer()->getMarker(), tossWin);
			serializeAndSend(client, response);
		} else if (clientRequest.message == "MOVE_REQUEST") {
			// Handle extracting values, and using get in perform / get move()
			get<0>(game.getCurrentPlayer()->nextMove) = get<0>(clientRequest.position);
			get<1>(game.getCurrentPlayer()->nextMove) = get<1>(clientRequest.position);
			if (game.canMoveAtPosition(get<0>(clientRequest.position), get<1>(clientRequest.position))) {
				game.playerGo();
				if (int winner = game.gameBoard.checkVictory()) {
					ServerResponse response(0, message="WINNER_DETECTED", winner, game.gameBoard.getBoardString());
    				serializeAndSend(client, response);
				}
				ServerResponse response(0, message="MOVE_RESPONSE", game.gameBoard.getBoardString(), game.getCurrentPlayer()->getMarker());
				serializeAndSend(client, response);					
			}
			else {
				ServerResponse response(1, "MOVE_RESPONSE");
				serializeAndSend(client, response);
			}
		}
	};
	client->onSocketClosed = [client](int errCode = 1) {
		cout << "[!] Socket closed:" << client->getRemoteAddress() << ":" << client->getRemotePort() << " -> " << errCode << endl;
		cout << flush;
	};
};

server.Bind("0.0.0.0", 8888);
server.Listen();

string input;
getline(cin, input);
while (input != "exit") {
	getline(cin, input);
}
server.Close();	
}


int main() {
	ServerApp server;
	server.begin();
	return 0;

}
