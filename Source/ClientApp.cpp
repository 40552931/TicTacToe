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

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind/bind.hpp>

using namespace std;

int main() {
	Client client;
	client.onMessageReceived = [](string message) {
		cout << "[*] Message from server: " << message << endl;
	};
	client.Connect("0.0.0.0", 8888, [&] {
		cout << "[*] Connected to server successfully \n" << endl;
	});
   

	string input;
    getline(cin, input);
    while (input != "exit")
    {
    	// Create new Message object with input
    	const Message msg(input);
    	std::stringstream messageStream;
    	boost::archive::text_oarchive archive(messageStream);
    	archive << msg;
    	string outboundData = messageStream.str();
    	client.Send(outboundData);
        getline(cin, input);
    }

    client.Close();

    return 0;
}
