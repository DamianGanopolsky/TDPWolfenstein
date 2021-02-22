#include "clients_connected.h"

ClientsConnected::ClientsConnected(NonBlockingQueue<Command*>& commands,
            NonBlockingQueue<ConnectionId*>& finished_connections) : 
            commands(commands), finished_connections(finished_connections), clients() {}

ClientsConnected::~ClientsConnected() {}

void ClientsConnected::add(const ConnectionId id, Socket& peer) {
    if (clients.count(id) > 0) {
        throw Exception("Repeated client_id.");
    }
    clients.emplace(
        std::piecewise_construct, std::forward_as_tuple(id),
        std::forward_as_tuple(peer, id, finished_connections, commands));
    clients.at(id).start();
}

void ClientsConnected::remove(const ConnectionId id) {
    if (clients.count(id) == 0) {
        throw Exception("Invalid client_id.");
    }
    clients.at(id).stop();
    clients.at(id).joinThreads();
    clients.at(id).join();
    clients.erase(id);
} 

void ClientsConnected::sendMessageToAll(Notification* message) {
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    std::shared_ptr<Notification> message_ptr(message);
    for (it = clients.begin(); it != clients.end(); it++) {
        it->second.push(message_ptr);
    }
}

void ClientsConnected::sendEventToAll(Notification* event) {
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    std::shared_ptr<Notification> event_ptr(event);
    for (it = clients.begin(); it != clients.end(); it++) {
        it->second.push(event_ptr);
    }
}

void ClientsConnected::sendEventToOne(ConnectionId id, Notification* event) {
    if (clients.count(id) == 0) {
        throw Exception("Invalid client_id.");
    }
    std::shared_ptr<Notification> event_ptr(event);
    clients.at(id).push(event_ptr);
}

void ClientsConnected::stop() { 
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    for (it = clients.begin(); it != clients.end();) {
        it->second.stop();
        it->second.joinThreads();
        it->second.join();
        it = clients.erase(it);
	}
}
