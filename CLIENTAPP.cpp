#include "Client.hpp"
#include <iostream>

using namespace std;



int main() {
	Client client;
	client.onMessageReceived = [](string message) {
		cout << "[*] Message from server: " << message << endl;
	};
	client.Connect("127.0.0.1", 8888, [&] {
		cout << "[*] Connected to server successfully" << endl;
		client.Send("Hello server!!!!!!!!!!");
	});

	string input;
    getline(cin, input);
    while (input != "exit")
    {
        client.Send(input);
        getline(cin, input);
    }

    client.Close();

    return 0;
}