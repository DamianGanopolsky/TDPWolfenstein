#include "clients_connected.h"

ClientsConnected::ClientsConnected(NonBlockingQueue<Command*>& commands,
            NonBlockingQueue<ConnectionId*>& finished_connections) : 
            commands(commands), finished_connections(finished_connections) {}

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
    clients.erase(id);
} 

void ClientsConnected::notify(const ConnectionId id, Notification* notification) {}

void ClientsConnected::notifyAll(Notification* notification) {}

//void ClientsConnected::changeMap(const ConnectionId id, const Id new_map) {}

/*void ClientsConnected::updateToAll(Notification* broadcast,
                const ConnectionId updated_client,
                const bool send_to_updated_client) {}*/

void ClientsConnected::sendMessageToAll(Notification* message) {
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    for (it = clients.begin(); it != clients.end(); it++) {
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
