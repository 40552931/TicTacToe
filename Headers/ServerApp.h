#include "../Headers/Client.h"
#include "../Headers/ServerResponse.h"
#include "../Headers/Server.h"

#include <string>

class ServerApp {
public:
	Server server;
	void serializeAndSend(Client*, ServerResponse);
	void begin();
	ClientRequest deserializeClientRequest(Client* client, std::string message);
};