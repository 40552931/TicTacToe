#include "../Headers/Server.hpp"
#include <iostream>
#include "../Headers/Message.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind/bind.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


using namespace std;

int main() {
	Server server;
	server.uponNewCon = [&](Client *client) {
		cout << "[!] New client connected: [" << client->remoteAddress() << "]" << endl;
		client->onMessageReceived = [client](string message) {
			istringstream ss(message);
			Move move;
			boost::archive::text_iarchive ia(ss);
			ia >> move;
			cout << "MOVE Y: " << move.y;
			cout << "[*] [" << client->remoteAddress() << "]:" << client->remotePort() << " => " << move.x << endl;
			client->Send("OK!");
		};
		client->onSocketClosed = [client](int errCode = 1) {
			cout << "[!] Socket closed:" << client->remoteAddress() << ":" << client->remotePort() << " -> " << errCode << endl;
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