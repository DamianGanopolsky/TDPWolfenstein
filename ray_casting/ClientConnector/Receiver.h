#ifndef __RECEIVER__
#define __RECEIVER__

#include "../Player.h"
#include "../Map_2d.h"
#include "../../Common/thread.h"
#include "../../Common/non_blocking_queue.h"
#include "../../Common/socket.h"
#include "../../Common/protocol.h"
#include "ReceiveController.h"
#include "ClientSocket.h"
#include "UpdateMessage.h"

class Receiver: public Thread {
public:
    Receiver(ClientSocket* ClientSocket,\
    NonBlockingQueue<UpdateMessage*>& RECV_QUEUE,ReceiveController& Recv_Controller):receiving(true),\
    clientsocket(ClientSocket),recv_queue(RECV_QUEUE),recv_controller(Recv_Controller){

    }

    void run() override;

    void stop();

private:
    bool receiving;
    ClientSocket* clientsocket;
    NonBlockingQueue<UpdateMessage*>& recv_queue;
    ReceiveController& recv_controller;
    //Player& player;
    //Map_2d& map;

};

#endif