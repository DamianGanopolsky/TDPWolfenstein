#include "./server.h" 

Server::Server(const char* service,const char* Map_yaml) : new_connections(),
									 accepter(service, new_connections),
									 loop(new_connections,Map_yaml) {}

Server::~Server() {}

void Server::operator()() {
	accepter.start();
	loop.start();
	char input;
	do {
		input = std::getchar();
	} while (input != 'q');
	accepter.stop();
	accepter.join();
	loop.stop();
	loop.join();
}
