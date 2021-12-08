#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

#include "../Headers/Client.h"
#include "../Headers/Message.hpp"
#include "../Headers/GameController.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind/bind.hpp>

using namespace std;

int main() {
	GameController game;
	Client client;
	client.onMessageReceived = [](string message) {
		cout << "[*] Message from server: " << message << endl;
	};
	client.Connect("0.0.0.0", 8888, [&] {
		cout << "[*] Connected to server successfully \n" << endl;
	});
   
    cout << "Welcome to the Tic Tac Toe Game" << endl;
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

    SendableObject sObj("Marker choice", markerChoice);
    std::stringstream messageStream;
    boost::archive::text_oarchive archive(messageStream);
    archive << sObj;
    string outboundData = messageStream.str();
    cout << "Sending: " << outboundData << endl;

    client.Send(outboundData);

    client.Close();

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