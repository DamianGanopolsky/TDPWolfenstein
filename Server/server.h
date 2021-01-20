#ifndef SERVER_H 
#define SERVER_H
#include <string>
#include <iostream>
#include <cstdlib>
#include "./accepter.h"
//-------------------------------------------------------------------------------
class Server {
	Accepter accepter;

	public: 
		explicit Server(const char* service, std::string& root);
		~Server();

		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;
		Server(Server&& other) = delete;
		Server& operator=(Server&& other) = delete;

		void operator()();
};
#endif
