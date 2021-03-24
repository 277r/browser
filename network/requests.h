// standard networking stuff
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#include <iostream>

#include "../libs/stringFunctions.h"
#include "../compression/compression.h"
// openssl header for secured socket
#include <openssl/ssl.h>


namespace request {
	// looks at port and parses argument to corresponding function
	char* getByUrl(std::string &url, unsigned int port);
	char *getraw(std::string &url, unsigned int port);
	// S stands for secure in this case
	char *getrawS(std::string &url, unsigned int port);
	void urlDecoder(std::string &url, unsigned int &port);
	

};