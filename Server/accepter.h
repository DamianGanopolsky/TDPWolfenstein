#ifndef ACCEPTER_H
#define ACCEPTER_H

#include <list>
#include <string>
#include <atomic>
#include <iostream>
#include "./login.h"
//#include "../Common/thread.h"
//#include "../Common/non_blocking_queue.h"
//#include "./connection_element.h"

class Accepter: public Thread {
	Socket socket;
	std::atomic<bool> keep_accepting;
	NonBlockingQueue<ConnectionElement*>& new_connections;
	std::list<Login> logins;
	void _joinReaper();
	void _joinThreads();
	public:
		explicit Accepter(const char* service, NonBlockingQueue<ConnectionElement*>& new_connections);
		~Accepter();
		
		Accepter(const Accepter&) = delete;
		Accepter operator=(const Accepter&) = delete;
		Accepter(Accepter&& other) = delete;
		Accepter operator=(Accepter&& other) = delete;

		void run() override;
		void stop();
};
#endif
