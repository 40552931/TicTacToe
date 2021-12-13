<<<<<<< HEAD
#include "../Headers/Client.h"
#include "../Headers/ServerResponse.h"
#include "../Headers/Server.h"

#include <string>

=======
#include <string>
#include "../Headers/Client.h"
#include "../Headers/Message.h"
#include "../Headers/Server.h"

>>>>>>> 9a93491a3ddf58a2ad0c7eebd8a77454df42e331
class ServerApp {
public:
	Server server;
	void serializeAndSend(Client*, ServerResponse);
	void begin();
	ClientRequest deserializeClientRequest(Client* client, std::string message);
};