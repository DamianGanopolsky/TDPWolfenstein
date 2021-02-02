#ifndef SERVER_H 
#define SERVER_H
#include <string>
#include <iostream>
#include <cstdlib>
#include "./accepter.h"
#include "./loop.h"

class Server {
	NonBlockingQueue<ConnectionElement*> new_connections;
	Accepter accepter;
	Loop loop;

	public: 
		explicit Server(const char* service);
		~Server();

		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;
		Server(Server&& other) = delete;
		Server& operator=(Server&& other) = delete;

		void operator()();
};
#endif
