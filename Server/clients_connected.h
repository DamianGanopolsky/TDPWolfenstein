#ifndef CLIENTS_CONNECTED_H
#define CLIENTS_CONNECTED_H

#include <unordered_map>
#include "../Common/defs.h"
#include "../Common/non_blocking_queue.h"
#include "clientHandler.h"
#include "../Commands/command.h"
#include "../Notifications/notification.h"

class ClientsConnected {
    std::unordered_map<ConnectionId, ClientHandler> clients;
    NonBlockingQueue<Command*>& commands;
    NonBlockingQueue<ConnectionId*>& finished_connections;
    
    public:
        ClientsConnected(NonBlockingQueue<Command*>& commands,
            NonBlockingQueue<ConnectionId*>& finished_connections);
        ~ClientsConnected();

        ClientsConnected(const ClientsConnected&) = delete;
		ClientsConnected operator=(const ClientsConnected&) = delete;
		ClientsConnected(ClientsConnected&& other) = delete;
		ClientsConnected operator=(ClientsConnected&& other) = delete;

        void add(const ConnectionId id, const Id map, Socket& peer);
        void remove(const ConnectionId id);
        void notify(const ConnectionId id, Notification* notification);
        void notifyAll(Notification* notification);
        //void changeMap(const ConnectionId id, const Id new_map);
        void updateToAll(Notification* broadcast,
                        const ConnectionId updated_client,
                        const bool send_to_updated_client);
        void sendMessageToAll(Notification* message);
        void sendEventToAll(Notification* event);
        void stop();
};

#endif
