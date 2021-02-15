#include "clients_connected.h"

ClientsConnected::ClientsConnected(NonBlockingQueue<Command*>& commands,
            NonBlockingQueue<ConnectionId*>& finished_connections) : 
            commands(commands), finished_connections(finished_connections), clients() {}

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
    clients.at(id).join();
    std::cout <<"ClientsConnected: borro client"<< std::endl;
    clients.erase(id);
    std::cout <<"ClientsConnected: erased client"<< std::endl;
} 

void ClientsConnected::sendMessageToAll(Notification* message) {
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    std::shared_ptr<Notification> message_ptr(message);
    for (it = clients.begin(); it != clients.end(); it++) {
        std::cout <<"ClientsConnected: push message"<< std::endl;
        it->second.push(message_ptr);
    }
}

void ClientsConnected::sendEventToAll(Notification* event) {
    std::cout <<"ClientsConnected: send()"<< std::endl;
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    std::shared_ptr<Notification> event_ptr(event);
    for (it = clients.begin(); it != clients.end(); it++) {
        std::cout <<"ClientsConnected: push event"<< std::endl;
        it->second.push(event_ptr);
    }
}

void ClientsConnected::sendEventToOne(ConnectionId id, Notification* event) {
    std::cout <<"ClientsConnected: sendToOne()"<< std::endl;
    if (clients.count(id) == 0) {
        throw Exception("Invalid client_id.");
    }
    std::shared_ptr<Notification> event_ptr(event);
    std::cout <<"ClientsConnected: push event"<< std::endl;
    clients.at(id).push(event_ptr);
}

void ClientsConnected::stop() { 
    std::cout <<"ClientsConnected: stop()"<< std::endl;
    std::unordered_map<ConnectionId, ClientHandler>::iterator it;
    for (it = clients.begin(); it != clients.end();) {
        std::cout <<"ClientsConnected: entro"<< std::endl;
        it->second.stop();
        it->second.joinThreads();
        it->second.join();
        std::cout <<"ClientsConnected: salio"<< std::endl;
        it = clients.erase(it);
        std::cout <<"ClientsConnected: termino"<< std::endl;
	}
}
