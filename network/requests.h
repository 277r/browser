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

namespace request {
	char *getraw(std::string url, unsigned int port);
	
};