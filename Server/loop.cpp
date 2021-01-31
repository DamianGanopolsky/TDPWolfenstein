#include "loop.h"

Loop::Loop(NonBlockingQueue<Socket*>& new_connections, Id map) : 
                game(clients_connected,map), 
                clients_connected(commands, finished_connections),
                commands(), 
                finished_connections(), 
                new_connections(new_connections),
                is_running(true),
                map(map) {}

Loop::~Loop() {}

void Loop::_newConnections() {
    Socket* peer = nullptr;
    while ((peer = this->new_connections.pop())) {
        ConnectionId id = this->game.newPlayer();
        clients_connected.add(id, *peer);
        delete peer;
    } 
}

void Loop::_newCommands() {
    Command* command = nullptr;
    while((command = this->commands.pop())) {
        try {
            command->run(this->game);
        } catch (const std::exception& e) {
            Notification* message = new Message(ERROR_MSSG, e.what());
            clients_connected.sendMessageToAll(message);
        }
    }
}

void Loop::_finishedConnections() {
    ConnectionId* connection = nullptr;
    while ((connection = finished_connections.pop())){
        game.deletePlayer(*connection);
        clients_connected.remove(*connection);
        delete connection;
    }
}

void Loop::run() {
    while (is_running) {
        int it = 0;
        _newConnections();
        _newCommands();
        game.updatePlayers(it);
        _finishedConnections();

        // tick rate
        // 30 tps
    }
    clients_connected.stop();
}

void Loop::stop() {
    this->is_running = false;
}