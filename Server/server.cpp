#include "./server.h" 

Server::Server(const char* service) : accepter(service) {}

Server::~Server() {}

void Server::operator()() {
	accepter.start();
	//loop.start();
	char input;
	do {
		input = std::getchar();
	} while (input != 'q');
	accepter.stop();
	//loop.stop();
	accepter.join();
}
