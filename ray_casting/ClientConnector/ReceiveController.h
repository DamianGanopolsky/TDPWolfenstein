#ifndef __RECEIVE_CONTROLLER__
#define __RECEIVE_CONTROLLER__

#include "../Player.h"
#include "../Map_2d.h"
#include "../../Common/non_blocking_queue.h"
#include "UpdateMessage.h"
#include "../Client.h"
#include "../../Common/protocol.h"
#include "../SdlClasses/SoundManager.h"
#include "../const.h"

/* ESta clase va a ir haciendo pop de la cola no bloqueante */

class ReceiveController {
public:
    ReceiveController(Player& Player,Map_2d& MAP,NonBlockingQueue<UpdateMessage*>&\
     RECV_QUEUE,Client& CLIENT);

    bool update();

private:
    SoundManager soundmanager;
    Player& player;
    Map_2d& map;
    NonBlockingQueue<UpdateMessage*>& recv_queue;
    Client& client;
    bool running;
    int lives;
    
};

#endif