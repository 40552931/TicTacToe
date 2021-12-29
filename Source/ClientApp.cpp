#include "../Headers/ClientApp.h"
#include "../Headers/Client.h"
#include "../Headers/ServerResponse.h"
#include "../Headers/ClientRequest.h"
#include "../Headers/Messages.h"
#include "../Headers/GameController.h"
#include "../Headers/Crypt.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind/bind.hpp>

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
#include <cmath>

using namespace std;

ClientApp::ClientApp() {
	// Define what happens upon message recieve
	client.onMessageReceived = [&](string message) mutable {
		onMessageReceive(message);
	};
}

void ClientApp::serializeAndSend(const ClientRequest clientRequest) {
    std::stringstream messageStream;
    // Create serialization archive
    boost::archive::text_oarchive archive(messageStream);
    // Pack archive with client request object
    archive << clientRequest;
    // Encrypt and send
    string outboundData = Crypt::decryptEncrypt(messageStream.str());
    client.Send(outboundData);	
}

ServerResponse ClientApp::deserializeServerResponse(const string message) {
	string decryptedMessage = Crypt::decryptEncrypt(message);
	istringstream stringStream(decryptedMessage);
	ServerResponse serverResponse;
	// Deserialize from archive and pack into response object, reading for reading.
	boost::archive::text_iarchive deserializedText(stringStream);
	deserializedText >> serverResponse;
	return serverResponse;
}

void ClientApp::onMessageReceive(const string message) {
	ServerResponse serverResponse = deserializeServerResponse(message);
	if (serverResponse.message == Response::BEGIN_GAME) {
		if (serverResponse.responseCode == 0) {
			cout << "[*] Response from server: OK - starting game." << endl;
		} else {
			cout << "[!] There was an issue starting the game" << endl;
		}
	}
	else if (serverResponse.message == Response::MARKER_CHOICE) {
		if (serverResponse.responseCode == 0) {
			string markerString = serverResponse.tossWin == 1 ? "Human" : "Computer";
			cout << "[*] " << markerString << " Has won the toss and will go first" << endl;
			cout << serverResponse.printableGameBoard << endl;
		} else {
			cout << "[!] There was an error with your marker choice... " << endl;
		}
	} else if (serverResponse.message == Response::MOVE) {
		if (serverResponse.responseCode == 0) {
			cout << "[*] Move completed" << endl;
			cout << serverResponse.printableGameBoard << endl;
		} else {
			cout << "[!] That space is already taken, please choose another..." << endl;
		}
	} else if (serverResponse.message == Response::WINNER_DETECTED) {
		// Handle winner
		cout << "[!] Winner detected, closing connection" << endl;
		cout << serverResponse.printableGameBoard << endl;
		endGameSequence(serverResponse.winner);
		client.Close();
		exit(0);
	} else {
		cout << "[!] Unusual response detected... contact a developer";
	}
}

void ClientApp::endGameSequence(int winner) {
	cout << "\n-= Game over =-\n" << endl;
	// Caused by serilization library bug
	if (winner > 100)
		winner = floor(winner/100); // Either 0, 1, 2
	if (winner == TIE_INDICATOR) {
		cout << "[*] Game was a draw: exiting" << endl;
		return;
	}
	string winnerString = winner == this->playerMarker ? "Human" : "Computer";
	cout << "[*] " << winnerString << " Has won the game!" << endl;
}

void ClientApp::askToPlay() {
	string type;
	do {
		cout << "[*] Would you like to begin the game? [y/n]: " << endl;
		cin >> type;
	} while (!cin.fail() && type!="y" && type!="n");
	if (type == "y") {
		ClientRequest beginGame(Request::BEGIN_GAME);
		serializeAndSend(beginGame);
	} else {
		exit(0);
	}
}

void ClientApp::beginConnection() {
	client.Connect("0.0.0.0", 8888, [&] {
		cout << "[*] Connected to server successfully" << endl;
	});
	cout << "[*] Welcome to the Tic Tac Toe Game" << endl;
	askToPlay();
}

void ClientApp::beginMarkerChoice() {
	bool isValidChoice = false;
    int markerChoice;
    do {
    	cout << "[*] Enter 1 for X or 2 for O: " << endl;
    	while(!(cin >> markerChoice)) {
    		cin.clear();
    		cin.ignore(1000, '\n');
    		cout << "[!] ERROR: Enter an integer!" << endl;
    		cout << "[*] Enter 1 for X or 2 for O: " << endl;
    	}
    	if (markerChoice != 1 && markerChoice != 2)
    		cout << "[!] ERROR: Enter 1 or 2!" << endl;
    	else
    		isValidChoice = true;
    } while (!isValidChoice);
    this->playerMarker = markerChoice;
    string markerString = markerChoice == 1 ? "X" : "O";
	cout << "[*] You have chosen: " << markerString << endl;
    ClientRequest sObj(Request::MARKER_CHOICE, markerChoice);
    serializeAndSend(sObj);
}

void ClientApp::beginMoveInputSequence() {
	while (1) {
		bool valid =false;
		int x, y;
		do {
			// wait a little, otherwise output gets swallowed..
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			cout << "[*] Enter X: ";
			while (!(cin >> x)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "[!] Enter a number" << endl;
			}
			cout << "[*] Enter Y: ";
			while (!(cin >> y)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "[!] Enter a number" << endl;
			}

			if (x < 1 || y < 1 || x > 3 || y > 3) {
				printf("[!] ERROR: Invalid X or Y!\n");
			}
			else {
				valid = true;
			}
		} while (!valid);
		ClientRequest sObj(Request::MOVE, make_tuple(x, y));
		serializeAndSend(sObj);
	}
}

int main() {
	ClientApp clientApp;
	clientApp.beginConnection();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	clientApp.beginMarkerChoice();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	clientApp.beginMoveInputSequence();
    clientApp.client.Close();
    return 0;
}