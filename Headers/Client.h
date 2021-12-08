#pragma once

#include "BasicSocket.h"

class Client : public BasicSocket {
public:
	std::function<void(std::string)> onMessageReceived;
	std::function<void(const char*, int)> onRawMessageReceived; // Msg and len
	std::function<void(int)> onSocketClosed;
	// Constructor
	Client(int socketId = -1) : BasicSocket(socketId) {}
	void Connect(uint32_t address, uint16_t port, std::function<void()> onConnected);
	void Connect(std::string host, uint16_t port, std::function<void()> onConnected);
	int Send(const char* bytes, size_t bytesLength);
	void Listen();
	void setAddressStruct(sockaddr_in);
	sockaddr_in getAddressStruct() const;
	int Send(std::string message);
private:
	static void Receive(Client*);
	void setTimeout(int);
};