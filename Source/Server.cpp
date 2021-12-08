#include "../Headers/Server.h"
#include <thread>

using namespace std;

Server::Server(): BasicSocket(-1) {
	setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &num, sizeof(int));
}

void Server::Bind(const char* ipAddress, uint16_t port) { // Could be str not char*?
	inet_pton(AF_INET, ipAddress, &this->address.sin_addr);
	this->address.sin_port = htons(port);
	this->address.sin_family = AF_INET; // TCP
	bind(this->sock, (const sockaddr *)&this->address, sizeof(this->address));
	printf("[*] Bound and listening on [%s]\n", ipAddress);
}

void Server::Listen() {
	listen(this->sock, 20);
	// create new thread, running Accept function and ready to recv client...
	// each thread acts as its own server for a client
	thread t(Accept, this);
	t.detach();
}

void Server::Accept(Server* server) {
	// get info about incoming connection
	sockaddr_in incomingConnectionInfo;
	socklen_t incomingConnectionInfoLength = sizeof(incomingConnectionInfo);
	int newSock;
	while (!server->closed) {
		// try and get the client, will be >= 0 if error
		newSock = accept(server->sock, (sockaddr*)&incomingConnectionInfo, &incomingConnectionInfoLength);
		if (!server->closed && newSock >= 0) {
			// create client instance from incoming connection info
			Client* client = new Client(newSock);
			client->setAddressStruct(incomingConnectionInfo);
			server->uponNewCon(client);
			// begin listening
			client->Listen();
		}
	}
}