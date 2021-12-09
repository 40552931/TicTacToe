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
			client->Send("OK!");
			if (sObj.indicator == "Marker choice") {
				// Set up player markers - see begingame
				int playerMarker = sObj.markerChoice;
				game.initializePlayers(playerMarker);
			} else if (sObj.indicator == "Move") {
				// Handle extracting values, and using get in perform / get move()
				get<0>(game.getCurrentPlayer()->nextMove) = get<0>(sObj.position);
				get<1>(game.getCurrentPlayer()->nextMove) = get<1>(sObj.position);
				game.playerGo();
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
