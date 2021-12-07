#include "../Headers/Client.hpp"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

#include "../Headers/Message.hpp"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind/bind.hpp>

using namespace std;

int main() {
	Client client;
	client.onMessageReceived = [](string message) {
		cout << "[*] Message from server: " << message << endl;
	};
	client.Connect("127.0.0.1", 8888, [&] {
		cout << "[*] Connected to server successfully \n" << endl;
	});
   

	int x, y;
	cout << "Enter X: ";
	while (!(cin >> x)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter a number";
	}
	cout << "Enter Y: ";
	while (!(cin >> y)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter a number";
	}

	Move move;
    move.x = x;
    move.y = y;
    std::stringstream messageStream;
    boost::archive::text_oarchive archive(messageStream);
    archive << move;
    string outboundData = messageStream.str();
    client.Send(outboundData);

    client.Close();

    return 0;
}