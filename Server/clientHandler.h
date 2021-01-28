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
#include "../Commands/command.h"
#include "../Notifications/notification.h"
#include "../Notifications/message.h"

class ClientHandler : public Thread {
	Socket peer;
	std::atomic<bool> is_running;
	ConnectionId id;
	NonBlockingQueue<ConnectionId*>& finished_connections;
	
	std::mutex m;
	int dead_threads;
	BlockingQueue<Notification*> notifications;
	NonBlockingQueue<Command*>& commands;
	std::thread send;
	std::thread receive;
	
	void _deadThread();
    void _send();
    void _receive();

	public:
		explicit ClientHandler(Socket& socket, const ConnectionId id, 
						NonBlockingQueue<ConnectionId*>& finished_connections,
                        NonBlockingQueue<Command*>& commands);
		~ClientHandler();

		ClientHandler(const ClientHandler&) = delete;
		ClientHandler operator=(const ClientHandler&) = delete;
		ClientHandler(ClientHandler&& other) = delete;
		ClientHandler operator=(ClientHandler&& other) = delete;

		void run() override;
    	//void push(Notification* notification);
		//void changeMap(Id map);
		bool isRunning() const;
		void joinThreads();
		void stop();
};
#endif
