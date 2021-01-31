#ifndef CLIENTS_CONNECTED_H
#define CLIENTS_CONNECTED_H

#include <unordered_map>

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
        void notify(const ConnectionId id, Notification* notification);
        void notifyAll(Notification* notification);
        //void changeMap(const ConnectionId id, const Id new_map);
        //void updateToAll(Notification* broadcast,
        //                const ConnectionId updated_client,
        //                const bool send_to_updated_client);
        void sendMessageToAll(Notification* message);
        void sendEventToAll(Notification* event);
        void stop();
};

#endif
