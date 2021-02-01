#ifndef LOOP_H
#define LOOP_H

#include "../Common/thread.h"
#include "./Model/game.h"
#include "./clients_connected.h"

class Loop : public Thread {
    Game game;
    ClientsConnected clients_connected;
    NonBlockingQueue<Command*> commands;
    NonBlockingQueue<ConnectionId*> finished_connections;
    NonBlockingQueue<Socket*>& new_connections;
    std::atomic<bool> is_running;
    Id map;
    void _newConnections();
    void _newCommands();
    void _finishedConnections();

    public:
        Loop(NonBlockingQueue<Socket*>& new_connections, Id map);
        ~Loop();

        Loop(const Loop&) = delete;
        Loop& operator=(const Loop&) = delete;
        Loop(Loop&& other) = delete;
        Loop& operator=(Loop&& other) = delete;

        void run() override;
        void stop();
};

#endif