#include <string>
#include "../Headers/Client.h"
#include "../Headers/Message.h"
#include "../Headers/Server.h"

class ServerApp {
public:
	Server server;
	void serializeAndSend(Client*, ServerResponse);
	void begin();
	ClientRequest deserializeClientRequest(Client* client, std::string message);
};