#include "./server.h" 

Server::Server(const char* service,const char* Map_yaml) : new_connections(),
									 accepter(service, new_connections),
									 loop(new_connections,Map_yaml) {}

Server::~Server() {}

void Server::operator()() {
	accepter.start();
	std::cout <<"Accepter: Se lanzo el accepter"<< std::endl;
	loop.start();
	std::cout <<"Loop: Se lanzo el loop"<< std::endl;
	char input;
	do {
		input = std::getchar();
	} while (input != 'q');
	accepter.stop();
	std::cout <<"Accepter: Se freno el accepter"<< std::endl;
	accepter.join();
	std::cout <<"Accepter: Se joineo el accepter"<< std::endl;
	loop.stop();
	std::cout <<"Loop: Se freno el loop"<< std::endl;
	loop.join();
	std::cout <<"Loop: Se joineo el loop"<< std::endl;
}
