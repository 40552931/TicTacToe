#include "Server.hpp"
#include <iostream>

using namespace std;

int main() {
	Server server;
	server.uponNewCon = [&](Client *client) {
		cout << "[!] New client connected: [" << client->remoteAddress() << "]" << endl;
		client->onMessageReceived = [client](string message) {
			cout << "[*] [" << client->remoteAddress() << "]:" << client->remotePort() << " => " << message << endl;
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