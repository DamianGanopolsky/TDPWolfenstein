#ifndef CLIENTS_CONNECTED_H
#define CLIENTS_CONNECTED_H

#include <unordered_map>
#include <memory>

//class Command;
#include "./client_handler.h"


class ClientsConnected {
    NonBlockingQueue<Command*>& commands;
    NonBlockingQueue<ConnectionId*>& finished_connections;
    std::unordered_map<ConnectionId, ClientHandler> clients;
    
    public:
        ClientsConnected(NonBlockingQueue<Command*>& commands,
            NonBlockingQueue<ConnectionId*>& finished_connections);
        ~ClientsConnected();

        ClientsConnected(const ClientsConnected&) = delete;
		ClientsConnected operator=(const ClientsConnected&) = delete;
		ClientsConnected(ClientsConnected&& other) = delete;
		ClientsConnected operator=(ClientsConnected&& other) = delete;

        void add(const ConnectionId id, Socket& peer);
        void remove(const ConnectionId id);
        void sendMessageToAll(Notification* message);
        void sendEventToAll(Notification* event);
        void stop();
};

#endif
