#include "loop.h"

Loop::Loop() : commands(), finished_connections(), 
                clients_connected(commands, finished_connections),
                game(clients_connected),
                is_running(true) {}

Loop::~Loop() {}

void Loop::_newConnections() {
    Socket* peer = nullptr;
    while ((peer = this->new_connections.pop())) {
        ConnectionId id = this->game.newPlayer();
        clients_connected.add(id, *peer);
        delete peer;
    } 
}

void Loop::run() {
    while (is_running) {
        _newConnections();
        // procesar comandos / requests de los clientes
        // avanzar las partidas going on
        // chequear conexiones que terminaron

        // tick rate
        // 30 tps
    }
    clients_connected.stop();
}

void Loop::stop() {
    this->is_running = false;
}