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
		game.beginGame();
		cout << "[!] New client connected: [" << client->getRemoteAddress() << "]" << endl;
		client->onMessageReceived = [client, game](string message) mutable {
			istringstream ss(message);
			SendableObject sObj;
			boost::archive::text_iarchive ia(ss);
			ia >> sObj;
			cout << "[*] [" << client->getRemoteAddress() << "]:" << client->getRemotePort() << " => " << sObj.indicator << endl;
			if (sObj.indicator == "MARKER_CHOICE") {
				// Set up player markers - see begingame
				int playerMarker = sObj.markerChoice;
				game.initializePlayers(playerMarker);
			} else if (sObj.indicator == "MOVE_REQUEST") {
				// Handle extracting values, and using get in perform / get move()
				get<0>(game.getCurrentPlayer()->nextMove) = get<0>(sObj.position);
				get<1>(game.getCurrentPlayer()->nextMove) = get<1>(sObj.position);
				if (game.canMoveAtPosition(get<0>(sObj.position), get<1>(sObj.position))) {
					cout << "yeah it can move: " << game.gameBoard.getValueAtPosition(get<0>(sObj.position), get<1>(sObj.position)) << endl;
					game.playerGo();
					if (int winner = game.checkVictory()) {
						game.endGame(winner);
						ServerResponse serverResponseObject("WINNER_DETECTED", winner);
	    				std::stringstream messageStream;
	    				boost::archive::text_oarchive archive(messageStream);
	    				archive << serverResponseObject;
	    				string outboundData = messageStream.str();
	    				cout << "sending data with message WINNER_DETECTED" << endl;
						client->Send(outboundData);
					}
					ServerResponse serverResponseObject("OK");
    				std::stringstream messageStream;
    				boost::archive::text_oarchive archive(messageStream);
    				archive << serverResponseObject;
    				string outboundData = messageStream.str();
    				cout << "sending data with message OK" << endl;
					client->Send(outboundData);
				}
				else {
					ServerResponse serverResponseObject("ERROR_SPACE_TAKEN");
    				std::stringstream messageStream;
    				boost::archive::text_oarchive archive(messageStream);
    				archive << serverResponseObject;
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
	cout << "bound" << endl;
	server.Listen();
	cout << "listening" << endl;

	string input;
	getline(cin, input);
	while (input != "exit") {
		getline(cin, input);
	}
	server.Close();
	return 0;

}
