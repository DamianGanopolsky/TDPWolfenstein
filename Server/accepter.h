#ifndef SERVER_ACCEPTER_H
#define SERVER_ACCEPTER_H
#include <list>
#include <string>
#include <atomic>
#include <iostream>
#include "../Common/socket.h"
#include "../Common/thread.h"
#include "./clientHandler.h"

class Accepter: public Thread {
	Socket socket;
	std::atomic<bool> keep_accepting;
	std::list<ClientHandler *> client_list;

	void _joinReaper();
	void _joinThreads();

	public:
		explicit Accepter(const char* service);
		~Accepter();
		
		Accepter(const Accepter&) = delete;
		Accepter operator=(const Accepter&) = delete;
		Accepter(Accepter&& other) = delete;
		Accepter operator=(Accepter&& other) = delete;

		void run() override;
		void stop();
};
#endif
