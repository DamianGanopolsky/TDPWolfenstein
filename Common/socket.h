#ifndef COMMON_SOCKET_H 
#define COMMON_SOCKET_H
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <errno.h>
#include <stdio.h>
#include "./exception.h"
#define QUEUE_SOCKETS 20
//-------------------------------------------------------------------------------
class Socket{
	private:
		int fd;
		explicit Socket(int fd);
		void _setServerAddresses(const char* service, addrinfo** results);
		void _setClientAddresses(const char* host, const char* service,
								addrinfo** results);
		void _bind(addrinfo* results);
		void _listen();
		void _connect(addrinfo* results);
		
	public:
		Socket();
		Socket(const char* host, const char* service);
		explicit Socket(const char* service);
		Socket(const Socket&) = delete;
		Socket& operator=(const Socket&) = delete;
		Socket(Socket&& other);
		Socket& operator=(Socket&& other);
		~Socket();
		Socket accept() const;
		ssize_t send(const char* buffer, size_t buffer_size) const;
		ssize_t receive(char* buffer, size_t buffer_size, 
						int& bytes_received) const;
		void shutdown(int how = SHUT_RDWR) const;
		void close();
};
#endif
