#pragma once

#include "BasicSocket.h"
#include "Client.h"

class Server : public BasicSocket {
public:
	Server();
	std::function<void(Client*)> uponNewCon;
	void Bind(const char*, uint16_t);
	void Listen();
	int num = 1;
private:
	static void Accept(Server*);
};