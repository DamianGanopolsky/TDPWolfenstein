#include "clients_connected.h"

ClientsConnected::ClientsConnected(NonBlockingQueue<Command*>& commands,
            NonBlockingQueue<ConnectionId*>& finished_connections) : 
            commands(commands), finished_connections(finished_connections) {}

ClientsConnected::~ClientsConnected() {}

void ClientsConnected::add(const ConnectionId id, Socket& peer) {
    if (clients.count(id) > 0) {
        throw Exception("Repeated client_id.");
    }
    std::cout <<"ClientsConnected: adding a new_connection"<< std::endl;
    clients.emplace(
        std::piecewise_construct, std::forward_as_tuple(id),
        std::forward_as_tuple(peer, id, finished_connections, commands));
    std::cout <<"ClientsConnected: starting new_connection"<< std::endl;
    clients.at(id).start();
    std::cout <<"ClientsConnected: new_connection added"<< std::endl;
}

void ClientsConnected::remove(const ConnectionId id) {
    if (clients.count(id) == 0) {
        throw Exception("Invalid client_id.");
    }
    clients.at(id).stop();
    clients.at(id).joinThreads();
    clients.erase(id);
} 

void ClientsConnected::sendMessageToAll(Notification* message) {
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    for (it = clients.begin(); it != clients.end(); it++) {
        std::cout <<"ClientsConnected: push message"<< std::endl;
        it->second.push(message);
    }
    delete message;
}

void ClientsConnected::sendEventToAll(Notification* event) {
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    for (it = clients.begin(); it != clients.end(); it++) {
        it->second.push(event);
    }
    delete event;
}

void ClientsConnected::stop() { 
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    for (it = clients.begin(); it != clients.end(); it++) {
		it->second.stop();
        it->second.joinThreads();
        clients.erase(it);
	}
}
