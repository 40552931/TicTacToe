#pragma once

#include "BasicSocket.h"

class Client : public BasicSocket {
public:
	std::function<void(std::string)> onMessageReceived;
	std::function<void(const char*, int)> onRawMessageReceived; // Msg and len
	std::function<void(int)> onSocketClosed;
	// Constructor
	Client(int socketId = -1) : BasicSocket(socketId) {}
	// Connect overload for numeric address (or sockaddr object)
	void Connect(uint32_t address, uint16_t port, std::function<void()> onConnected);
	// Connect overload for string address
	void Connect(std::string host, uint16_t port, std::function<void()> onConnected);
	// Send overload for char* bytes send
	int Send(const char* bytes, size_t bytesLength);
	// Send overload for sending a std::string
	int Send(std::string message);
	void Listen();
	void setAddressStruct(sockaddr_in);
	sockaddr_in getAddressStruct() const;
private:
	static void Receive(Client*);
	void setTimeout(int);
};