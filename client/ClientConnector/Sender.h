#ifndef __SENDER__
#define __SENDER__

#include "../../Common/thread.h"
#include "../../Common/blocking_queue.h"
#include "../../Common/socket.h"
#include "Command.h"
#include "ClientSocket.h"

class Sender: public Thread {
public:
    Sender(ClientSocket* ClientSocket,BlockingQueue<Command*>& send_queue): \
    sending(true),clientsocket(ClientSocket),SendQueue(send_queue){

    }

    void run() override;

    void send(int u);

    void stop();

private:
    bool sending;
    ClientSocket* clientsocket;
    BlockingQueue<Command*>& SendQueue;

};

#endif