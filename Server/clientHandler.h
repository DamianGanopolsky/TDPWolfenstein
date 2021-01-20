#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#define BUFF_SIZE 64

#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>

#include "../Common/thread.h"
#include "../Common/socket.h"
#include "../Common/blocking_queue.h"
#include "../Common/non_blocking_queue.h"
#include "../Common/defs.h"
//-------------------------------------------------------------------------------
class ClientHandler {
	Socket peer;
	ConnectionId id;
	NonBlockingQueue<ConnectionId*>& finished_connections;
	std::mutex m;
	int dead_threads;
	std::thread send;
	std::thread receive;
	
	void _deadThread();
    void _send();
    void _receive();

	public:
		explicit ClientHandler(Socket& socket, const ConnectionId id, 
						NonBlockingQueue<ConnectionId*>& finished_connections);
		~ClientHandler();

		ClientHandler(const ClientHandler&) = delete;
		ClientHandler operator=(const ClientHandler&) = delete;
		ClientHandler(ClientHandler&& other) = delete;
		ClientHandler operator=(ClientHandler&& other) = delete;

		void start();
    	//void push(Notification* notification);
		//void changeMap(Id map);
		void joinThreads();
		void stop();
};
#endif
