#pragma once

#include "Client.hpp"
#include <thread>

using namespace std;
// Inherit everything from basic socket, bcos server is just a socket
class Server : public BasicSocket {
public:
	function<void(Client *)> uponNewCon = [](Client* client){};
	int num = 1;
	Server(): BasicSocket() { 
		setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &num, sizeof(int));
	};

	void Bind(const char *ipAddress, uint16_t port) {
		/// convert ipv4 to binary, output to this->address.sin_addr
		inet_pton(AF_INET, ipAddress, &this->address.sin_addr);
		// set port and prototype
		this->address.sin_port = htons(port);
		this->address.sin_family = AF_INET; // tcp
		// bind name to socket
		bind(this->sock, (const sockaddr *)&this->address, sizeof(this->address));
		printf("[*] Bound and listening on [%s]\n", ipAddress);
	}

	void Listen() {
		listen(this->sock, 20);
		thread t(Accept, this);
		t.detach();
	}

private:
	static void Accept(Server *server) {
		// get info about incoming connection
		sockaddr_in incomingConnectionInfo;
		socklen_t incomingConnectionInfoLength = sizeof(incomingConnectionInfo);
		int newSock;
		while(!server->closed) {
			// try and get the client, will be >= 0 if error
			newSock = accept(server->sock, (sockaddr*)&incomingConnectionInfo, &incomingConnectionInfoLength);
			if(!server->closed && newSock >= 0) {
				// create client instance from incoming connection info
				Client *client = new Client(newSock);
				client->setAddressStruct(incomingConnectionInfo);
				server->uponNewCon(client);
				// begin listening
				client->Listen();
			}
		}
	}
};
