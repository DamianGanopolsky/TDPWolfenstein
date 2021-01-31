#ifndef __SENDER__
#define __SENDER__

#include "../../Common/thread.h"
#include "../../Common/blocking_queue.h"
#include "../../Common/socket.h"
#include "ClientSocket.h"

class Sender: public Thread {
public:
    Sender(ClientSocket* ClientSocket): sending(true),clientsocket(ClientSocket){

    }

    void run() override;

    void send(int u);

    void stop();

private:
    bool sending;
    ClientSocket* clientsocket;
    //Player& player;
    //Map_2d& map;

};

#endif