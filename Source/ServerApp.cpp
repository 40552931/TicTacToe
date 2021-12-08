#include "../Headers/Server.h"

#include <iostream>
#include "../Headers/Message.hpp"
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
		cout << "[!] New client connected: [" << client->getRemoteAddress() << "]" << endl;
		client->onMessageReceived = [client](string message) {
			istringstream ss(message);
			Message receivedMessage;
			boost::archive::text_iarchive ia(ss);
			ia >> receivedMessage;
			cout << "[*] [" << client->getRemoteAddress() << "]:" << client->getRemotePort() << " => " << receivedMessage.contents << endl;
			client->Send("OK!");
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
