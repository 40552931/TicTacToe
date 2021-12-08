#include <iostream>
#include <string>

#include "../Headers/BasicSocket.h"

using namespace std;

BasicSocket::BasicSocket(int socketId = -1) {
	/* Class constructor method */
	if (socketId < 0) {
		// If error (>0) while creating socket...
		if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			cout << "[!] Error creating socket: " << errno << endl;
	}
	else {
		this->sock = socketId;
	}
}

string BasicSocket::ipToString(sockaddr_in ipAddressToConvert) {
	/* Convert given IP address from binary to a string */
	char ip[INET_ADDRSTRLEN];
	// inet_ntop() - convert IPv4 address from binary to text
	inet_ntop(AF_INET, &(ipAddressToConvert.sin_addr), ip, INET_ADDRSTRLEN);
	return string(ip);
}

void BasicSocket::Close() {
	if (closed) return;
	closed = true;
	close(sock);
	return;
}

string BasicSocket::getRemoteAddress() {
	return ipToString(address);
}

int BasicSocket::getRemotePort() {
	// converts the unsigned netshort from network byte order to host byte order.
	return ntohs(address.sin_port);
}