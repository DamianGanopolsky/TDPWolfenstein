#ifndef __RECEIVE_CONTROLLER__
#define __RECEIVE_CONTROLLER__

#include "../Player.h"
#include "../Map_2d.h"
#include "../../Common/non_blocking_queue.h"

/* ESta clase va a ir haciendo pop de la cola no bloqueante */

class ReceiveController {
public:
    ReceiveController(Player& PLAYER,Map_2d& MAP):player(PLAYER),map(MAP){
    }

    void ExecuteEvent();

private:
    Player& player;
    Map_2d& map;
    
};

#endif