#include "clients_connected.h"

ClientsConnected::ClientsConnected(NonBlockingQueue<Command*>& commands,
            NonBlockingQueue<ConnectionId*>& finished_connections) : 
            commands(commands), finished_connections(finished_connections) {}

ClientsConnected::~ClientsConnected() {}

void ClientsConnected::add(const ConnectionId id, const Id map, Socket& peer) {}

void ClientsConnected::remove(const ConnectionId id) {} 

void ClientsConnected::notify(const ConnectionId id, Notification* notification) {}

void ClientsConnected::notifyAll(Notification* notification) {}

//void ClientsConnected::changeMap(const ConnectionId id, const Id new_map) {}

void ClientsConnected::updateToAll(Notification* broadcast,
                const ConnectionId updated_client,
                const bool send_to_updated_client) {}

void ClientsConnected::sendMessageToAll(Notification* message) {}

void ClientsConnected::sendEventToAll(Notification* event) {}

void ClientsConnected::stop() {}
