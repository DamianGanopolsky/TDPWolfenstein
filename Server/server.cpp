#include "./server.h" 
//-------------------------------------------------------------------------------
Server::Server(const char* service) : accepter(service) {}

Server::~Server() {}

void Server::operator()() {
	accepter.start();
	char input;
	do {
		input = std::getchar();
	} while (input != 'q');
	accepter.stop();
	accepter.join();
}
