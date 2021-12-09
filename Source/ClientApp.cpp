#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

#include "../Headers/ClientApp.h"
#include "../Headers/Client.h"
#include "../Headers/Message.hpp"
#include "../Headers/GameController.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind/bind.hpp>

using namespace std;

ClientApp::ClientApp() {
	client.onMessageReceived = [&](string message) mutable {
		onMessageReceive(message);
	};
}

void ClientApp::onMessageReceive(string message) {
	istringstream ss(message);
	ServerResponse serverResponseObject;
	boost::archive::text_iarchive ia(ss);
	ia >> serverResponseObject;
	if (serverResponseObject.message == "OK") {
		// Handle OK
		cout << "Server says OK!" << endl;
	} else if (serverResponseObject.message == "ERROR_SPACE_TAKEN") {
		// Handle error
		cout << "You can't move there!" << endl;
	} else if (serverResponseObject.message == "WINNER_DETECTED") {
		// Handle winner
		cout << "Winner detected, closing connection" << endl;
		game.endGame(serverResponseObject.winner);
		client.Close();
		exit(0);
		cout << "da fuck"<<endl;
	} else {
		cout << "got a weird one...";
	}
}

void ClientApp::beginConnection() {
	client.Connect("0.0.0.0", 8888, [&] {
		cout << "[*] Connected to server successfully" << endl;
	});
	cout << "Welcome to the Tic Tac Toe Game" << endl;
}

void ClientApp::serializeAndSend(SendableObject sObj) {
    std::stringstream messageStream;
    boost::archive::text_oarchive archive(messageStream);
    archive << sObj;
    string outboundData = messageStream.str();
    client.Send(outboundData);	
}

void ClientApp::beginMarkerChoice() {
	bool isValidChoice = false;
    int markerChoice;
    do {
    	cout << "Enter 1 for X or 2 for O: " << endl;
    	while(!(cin >> markerChoice)) {
    		cin.clear();
    		cin.ignore(1000, '\n');
    		cout << "ERROR: Enter an integer!" << endl;
    		cout << "Enter 1 for X or 2 for O: " << endl;
    	}
    	if (markerChoice != 1 && markerChoice != 2)
    		cout << "ERROR: Enter 1 or 2!" << endl;
    	else
    		isValidChoice = true;
    } while (!isValidChoice);
    SendableObject sObj("MARKER_CHOICE", markerChoice);
    serializeAndSend(sObj);
}

void ClientApp::beginMoveInputSequence() {
	while (1) {
		bool valid =false;
		int x, y;
		do {
			cout << "Enter X: " << endl;
			while (!(cin >> x)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Enter a number" << endl;
			}
			cout << "Enter Y: " << endl;
			while (!(cin >> y)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Enter a number" << endl;
			}

			if (x < 1 || y < 1 || x > 3 || y > 3) {
				printf("ERROR: Invalid X or Y!\n");
			}
			else {
				valid = true;
			}
		} while (!valid);
		SendableObject sObj("MOVE_REQUEST", x, y);
		serializeAndSend(sObj);
	}
}



int main() {
	ClientApp clientApp;
	clientApp.beginConnection();
	clientApp.beginMarkerChoice();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	clientApp.beginMoveInputSequence();

    clientApp.client.Close();
    return 0;
}

/*class ClientApp {
public:
	void sendMarkerChoice() {
	    while (input != "exit")
	    {
	    	// Create new Message object with input
	    	const MarkerChoiceRequest msg(input);
	    	std::stringstream messageStream;
	    	boost::archive::text_oarchive archive(messageStream);
	    	archive << msg;
	    	string outboundData = messageStream.str();
	    	client.Send(outboundData);
	        getline(cin, input);
	    }
	}

	void sendMove() {

	}
};*/