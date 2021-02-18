#ifndef LOOP_H
#define LOOP_H

#include "../Common/thread.h"
#include "./Model/pre_game.h"
#include "./clients_connected.h"
#include "./connection_element.h"

class Loop : public Thread {
    Id map;
    int rate;
    PreGame pre_game;
    ClientsConnected clients_connected;
    NonBlockingQueue<Command*> commands;
    NonBlockingQueue<ConnectionId*> finished_connections;
    NonBlockingQueue<ConnectionElement*>& new_connections;
    std::atomic<bool> is_running;
    void _newConnections();
    void _newCommands();
    void _finishedConnections();
    void _deleteQueues();

    public:
        Loop(NonBlockingQueue<ConnectionElement*>& new_connections,const char* mapYaml);
        ~Loop();

        Loop(const Loop&) = delete;
        Loop& operator=(const Loop&) = delete;
        Loop(Loop&& other) = delete;
        Loop& operator=(Loop&& other) = delete;

        void run() override;
        void stop();
};

#endif