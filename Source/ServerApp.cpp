#include "../Headers/Server.h"

#include <iostream>
#include "../Headers/Message.hpp"
#include "../Headers/GameController.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind/bind.hpp>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

int main() {
	Server server;
	server.uponNewCon = [&](Client *client) {
		GameController game;
		cout << "[!] New client connected: [" << client->getRemoteAddress() << "]" << endl;
		client->onMessageReceived = [client, game](string message) mutable {
			istringstream ss(message);
			ClientRequest sObj;
			boost::archive::text_iarchive ia(ss);
			ia >> sObj;
			cout << "[*] [" << client->getRemoteAddress() << "]:" << client->getRemotePort() << " => " << sObj.message << endl;
			if (sObj.message == "BEGIN_GAME_REQUEST") {
				game.beginGame();
				ServerResponse response(0, message="BEGIN_GAME_RESPONSE");
    			std::stringstream messageStream;
    			boost::archive::text_oarchive archive(messageStream);
    			archive << response;
    			string outboundData = messageStream.str();
				client->Send(outboundData);
			}
			else if (sObj.message == "MARKER_CHOICE_REQUEST") {
				// Set up player markers - see begingame
				int playerMarker = sObj.markerChoice;
				game.initializePlayers(playerMarker);
				ServerResponse response(0, message="MARKER_CHOICE_RESPONSE", game.gameBoard.getBoardString(), game.getCurrentPlayer()->getMarker());
    			std::stringstream messageStream;
    			boost::archive::text_oarchive archive(messageStream);
    			archive << response;
    			string outboundData = messageStream.str();
				client->Send(outboundData);
			} else if (sObj.message == "MOVE_REQUEST") {
				// Handle extracting values, and using get in perform / get move()
				get<0>(game.getCurrentPlayer()->nextMove) = get<0>(sObj.position);
				get<1>(game.getCurrentPlayer()->nextMove) = get<1>(sObj.position);
				if (game.canMoveAtPosition(get<0>(sObj.position), get<1>(sObj.position))) {
					game.playerGo();
					if (game.checkVictory()) {
						int winner = game.checkVictory();
						game.endGame(winner);
						ServerResponse response(0, message="WINNER_DETECTED", winner, game.gameBoard.getBoardString());
	    				std::stringstream messageStream;
	    				boost::archive::text_oarchive archive(messageStream);
	    				archive << response;
	    				string outboundData = messageStream.str();
						client->Send(outboundData);
					}
					ServerResponse response(0, message="MOVE_RESPONSE", game.gameBoard.getBoardString(), game.getCurrentPlayer()->getMarker());
    				std::stringstream messageStream;
    				boost::archive::text_oarchive archive(messageStream);
    				archive << response;
    				string outboundData = messageStream.str();
					client->Send(outboundData);
				}
				else {
					ServerResponse response(1, "MOVE_RESPONSE");
    				std::stringstream messageStream;
    				boost::archive::text_oarchive archive(messageStream);
    				archive << response;
    				string outboundData = messageStream.str();
					client->Send(outboundData);
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
	return 0;

}
