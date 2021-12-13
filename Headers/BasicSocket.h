#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <functional>

class BasicSocket {
public:
	const uint16_t BUFSIZE = 0xFFFF;
	void Close();
	std::string getRemoteAddress();
	int getRemotePort();
	sockaddr_in address;
	bool closed = false;
protected:
	BasicSocket(int);
	static std::string ipToString(sockaddr_in);
	int sock = 0;
};