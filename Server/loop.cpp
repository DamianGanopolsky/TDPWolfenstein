#include "loop.h"

Loop::Loop() : commands(), finished_connections(), 
                clients_connected(commands, finished_connections),
                game(clients_connected),
                is_running(true) {}

Loop::~Loop() {}

void Loop::run() {
    while (is_running) {

    }
    clients_connected.stop();
}

void Loop::stop() {
    this->is_running = false;
}