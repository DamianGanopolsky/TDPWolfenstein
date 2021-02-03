#ifndef __RECEIVE_CONTROLLER__
#define __RECEIVE_CONTROLLER__

#include "../Player.h"
#include "../Map_2d.h"
#include "../../Common/non_blocking_queue.h"
#include "UpdateMessage.h"

/* ESta clase va a ir haciendo pop de la cola no bloqueante */

class ReceiveController {
public:
    ReceiveController(Player& PLAYER,Map_2d& MAP,NonBlockingQueue<UpdateMessage*>&\
     RECV_QUEUE):player(PLAYER),map(MAP),recv_queue(RECV_QUEUE){
    }

    void ExecuteEvent();

private:
    Player& player;
    Map_2d& map;
    NonBlockingQueue<UpdateMessage*>& recv_queue;
    
};

#endif