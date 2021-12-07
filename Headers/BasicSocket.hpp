#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <functional>
#include <cerrno>

using namespace std;

class BasicSocket {
public:
	sockaddr_in address;
	bool closed = false;
	const uint16_t BUFSIZE = 0xFFFF;

protected:
	int sock = 0;
	static string ipToString(sockaddr_in ip) {
		/* Convert given IP address to string */
		char _ip[INET_ADDRSTRLEN];
		// inet_ntop() - convert IPv4 address from binary to text.
		inet_ntop(AF_INET, &(ip.sin_addr), _ip, INET_ADDRSTRLEN);
		// convert to cpp string and return.
		return string(_ip);
	}

	BasicSocket(int socketId = -1) {
		/* Class constructor method */
		if (socketId < 0) {
			// Try and bind socket, give error is response code is indicative of an error...
			if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
				printf("Error creating socket");
			}
		} else {
			this->sock = socketId;
		}
	}

public:
	void Close() {
		if (closed) return;
		closed = true;
		close(this->sock);
		return;
	}

	string remoteAddress() {
		return ipToString(this->address);
	}

	int remotePort() {
		return ntohs(this->address.sin_port);
	}
};