#include "./accepter.h"

Accepter::Accepter(const char* service, NonBlockingQueue<ConnectionElement*>& new_connections) : 
					socket(service), keep_accepting(false), new_connections(new_connections) {}

Accepter::~Accepter() {}

void Accepter::run() {
	keep_accepting = true;
	try {
		while(keep_accepting){
			Socket peer = socket.accept();
			new_connections.push(new ConnectionElement(peer));
			std::cout <<"Accepter: Se connecto un peer"<< std::endl;
		}
	} catch (const std::exception& e) {
		std::cout <<"Accepter: Error en peer"<< std::endl;
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
