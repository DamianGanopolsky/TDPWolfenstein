#include "./socket.h"
#include <iostream>
//-------------------------------------------------------------------------------
void Socket::_setServerAddresses(const char* service, addrinfo** results) {
	addrinfo hints;	
	memset(&hints, 0, sizeof(struct addrinfo));   	
   	hints.ai_family = AF_INET;          	
   	hints.ai_socktype = SOCK_STREAM;    	
   	hints.ai_flags = AI_PASSIVE;             
   	if (::getaddrinfo(NULL, service, &hints, results)) {
   		throw Exception("Error in getaddrinfo server");
   	} 
}
void Socket::_setClientAddresses(const char* host, const char* service, 
								addrinfo** results) {
	addrinfo hints;	
	memset(&hints, 0, sizeof(struct addrinfo));   	
   	hints.ai_family = AF_INET;          	
   	hints.ai_socktype = SOCK_STREAM;    	
   	hints.ai_flags = 0;          
   	if (::getaddrinfo(host, service, &hints, results)) {
   		throw Exception("Error in getaddrinfo client");
   	} 
}

void Socket::_bind(addrinfo* results) {
	struct addrinfo *ptr;
	int temp = 0;
	for (ptr = results; ptr != NULL; ptr = ptr->ai_next) {
		temp = ::socket(ptr->ai_family, ptr->ai_socktype,
    						ptr->ai_protocol);
	   	if (temp == -1) { 
	   		continue;
	   	}
		int val = 1;
	   	if (::setsockopt(temp, SOL_SOCKET, SO_REUSEADDR, 
	   		&val, sizeof(val)) == -1) {     
	   		continue;
	    }
	    if (::bind(temp, results->ai_addr, results->ai_addrlen) == 0) {
	    	break;
	    } 
	    ::close(temp);
	}
	if (results == NULL) {
		throw Exception("Error in bind, couldn't find a node to bind");
	} else {
		fd = temp;
	}
}

void Socket::_listen() {
	if (::listen(this->fd, QUEUE_SOCKETS) == -1) {
	   	throw Exception("Error in listen");
	}
}

void Socket::_connect(addrinfo* results) {
	struct addrinfo *ptr;
	int temp = 0;
    for (ptr = results; ptr != NULL; ptr = ptr->ai_next) {
    	temp = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
   		if (temp == -1) {
	   		continue;
   		}
   		if (::connect(temp, ptr->ai_addr, ptr->ai_addrlen) == 0) {
   			break;
   		} 
   		::close(temp);
    }
    if (results == NULL) {
		throw Exception("Error in connect, couldn't find a node to connect");
	} else {
		fd = temp;
	}
}
//Para conectarme con el server
Socket::Socket(const char* host, const char* service) {
	addrinfo* results;
	_setClientAddresses(host, service, &results);
	try {
		_connect(results);
	} catch (const Exception& e) {
		::freeaddrinfo(results);
		throw;
	}
	::freeaddrinfo(results);
}

Socket::Socket(const char* service) {
	addrinfo* results;
	_setServerAddresses(service, &results);
	try {
		_bind(results);
		_listen();
	} catch (const Exception& e) {
		::freeaddrinfo(results);
		throw;
	}
	::freeaddrinfo(results);
}

Socket::Socket(Socket&& other) {
	this->fd = other.fd;
	other.fd = -1;
}
Socket& Socket::operator=(Socket&& other) {
	this->fd = other.fd;
	other.fd = -1;
	return *this;
}

Socket::Socket(int fd) : fd(fd) {}

Socket::~Socket() {
	if (fd == -1) return;
	::shutdown(fd, SHUT_RDWR);
	::close(fd);
}

Socket Socket::accept() const {
	int accepted = ::accept(fd, NULL, NULL);
	if (accepted == -1) {
		throw Exception("Error in accept");
	}
	return Socket(accepted);
}

ssize_t Socket::send(const char* buffer, size_t buffer_size) const {
	size_t total_sent = 0;
	//std::cout <<"Socket: Se envio un buffer de bytes"<< std::endl;
	while (total_sent < buffer_size) {
		ssize_t last_sent = ::send(fd, &buffer[total_sent], buffer_size-total_sent,
							MSG_NOSIGNAL);
		
		if (last_sent == -1) {
			throw Exception("Error in send");
		} else if (last_sent == 0){
			return 0;
		} else {
			total_sent += last_sent;
		}
	}
	return total_sent;
}

ssize_t Socket::receive(char* buffer, size_t buffer_size, 
						int& bytes_received) const {
	size_t total_recv = 0;
	bytes_received = 0;
	//std::cout <<"Socket: Se recibio un buffer de bytes"<< std::endl;
	while (total_recv < buffer_size) {
		ssize_t last_recv = ::recv(fd, &buffer[total_recv], 
									buffer_size-total_recv, 0);
		if (last_recv == -1) {
			throw Exception("Error in receive");
		} else if (last_recv == 0){
			return 0;
		} else {
			total_recv += last_recv;
			bytes_received += last_recv;
		}
	}
	return total_recv;
}

void Socket::shutdown(int how) const {
	if (fd != -1) {
		if (::shutdown(fd, how) != 0) {
			throw Exception("Error in shutdown");
		}
	}
}

void Socket::close() {
	if (fd != -1) {
		if (::close(fd) == -1) {
			throw Exception("Error in close");
		}
		fd = -1;
	}
}
