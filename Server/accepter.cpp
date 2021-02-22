#include "./accepter.h"

Accepter::Accepter(const char* service, NonBlockingQueue<ConnectionElement*>& new_connections) : 
					socket(service), keep_accepting(false), 
					new_connections(new_connections),
					logins() {}

Accepter::~Accepter() {
	_joinThreads();
}

void Accepter::_joinReaper() {
    for (auto it = logins.begin(); it != logins.end();) {
        if (it->isRunning()) {
            it->join();
            it = logins.erase(it);
        } else {
            it++;
        }
    }
}

void Accepter::_joinThreads() {
    for (auto it = logins.begin(); it != logins.end();) {
        it->stop();
        it->join();
        it = logins.erase(it);
    }
}

void Accepter::run() {
	keep_accepting = true;
	try {
		while(keep_accepting){
			Socket peer = std::move(socket.accept());
			//new_connections.push(new ConnectionElement(peer));
			logins.emplace_back(peer, new_connections);
			logins.back().start();
			_joinReaper();
		}
	} catch (const std::exception& e) {
		std::cout <<"Accepter: Error en peer"<< std::endl;
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cout <<"Accepter: Unknown error"<< std::endl;
	}
	_joinThreads();
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
