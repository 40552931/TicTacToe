#include "../Headers/Client.h"
#include "../Headers/BasicSocket.h"
#include <cstring>
#include <functional>
#include <thread>
#include <iostream>

using namespace std;


void Client::Connect(string host, uint16_t port, function<void()> onConnected) {
	// hints is a struct that contains info about socket, such a prototype, socktype, etc
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints)); // segfault if no
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	struct addrinfo *result, *rp;
	int status;
	// get info about server
	status = getaddrinfo(host.c_str(), NULL, &hints, &result);
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		// if item in result is ipv4 (server)
		if (rp->ai_family == AF_INET) {
			// save rp->ai_addr (server address) into this->address
			memcpy((void*)(&this->address), (void*)rp->ai_addr, sizeof(sockaddr_in));
			break;
		}
	}
	// release memory for "result" linked list
	freeaddrinfo(result);
	this->Connect((uint32_t)this->address.sin_addr.s_addr, port, onConnected);
}

void Client::Connect(uint32_t address, uint16_t port, function<void()> onConnected) {
	// set TCP, set port, set address
	this->address.sin_family = AF_INET;
	this->address.sin_port = htons(port);
	this->address.sin_addr.s_addr = address;
	// timeout for incase something goes wrong... don't wait forever
	this->setTimeout(5);
	// try to connect.. if response code is < 0 (error)...
	if (connect(this->sock, (const sockaddr *)&this->address, sizeof(sockaddr_in)) < 0) {
		cout << "[!] Connection to the host has failed: " << errno << endl;
		this->setTimeout(0);
		return;
	}
	this->setTimeout(0);
	onConnected();
	// begin listening
	this->Listen();
}

int Client::Send(const char *bytes, size_t bytesLength) {
	if (this->closed) {
		return -1;
	}
	// count bytes sent.. return that
	int sent = 0;
	sent = send(this->sock, bytes, bytesLength, 0);
	return sent;
}

int Client::Send(string message) {
	return this->Send(message.c_str(), message.length());
}

void Client::Listen() {
	// new thread with receive method
	thread t(Client::Receive, this);
	t.detach();
}

void Client::setAddressStruct(sockaddr_in addr) {
	this->address = addr;
}

sockaddr_in Client::getAddressStruct() const { return this->address; }

void Client::Receive(Client *client) {
	// receiving message
	char tempBuf[client->BUFSIZE];
	int messageLength;
	while ((messageLength = recv(client->sock, tempBuf, client->BUFSIZE, 0)) > 0) {
		tempBuf[messageLength] = '\0';
		if (client->onMessageReceived) {
			client->onMessageReceived(string(tempBuf, messageLength));
		}
		if (client->onRawMessageReceived) {
			client->onRawMessageReceived(tempBuf, messageLength);
		}
	}

	client->Close();
	//if(socket->onSocketClosed) { socket->onSocketClosed(errno); }
	//if (socket != nullptr) { delete socket; }
}

void Client::setTimeout(int secs) {
	struct timeval tv;
	tv.tv_sec = secs;
	tv.tv_usec = 0;
	// set socket timeout
	setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
}