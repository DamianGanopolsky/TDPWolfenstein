#include "./accepter.h"
#include "../Common/socket.h"

Accepter::Accepter(const char* service) : socket(service), keep_accepting(false) {}

Accepter::~Accepter() {}

void Accepter::run() {
	keep_accepting = true;
	try {
		Socket peer = socket.accept();
		new_connections.push(&peer);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void Accepter::stop() {
	keep_accepting = false; 
	try{
		socket.shutdown();
		socket.close();
	} catch (const Exception& e) {
		std::cerr << "Error while shutingdown accepter: "<< e.what() 
														<< std::endl;
	}
}
