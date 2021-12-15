#include <string>

class Crypt {
public:
	static std::string decryptEncrypt(std::string message) {
		// remove in production
		char key = 'Z'; // encryption key, keep secret in production.
		std::string encrypted = message;
	    for (int i = 0; i < message.size(); i++)
	        encrypted[i] = message[i] ^ key;   
	    return encrypted;
	}
};