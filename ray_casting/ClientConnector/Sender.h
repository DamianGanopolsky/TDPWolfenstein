#ifndef __SENDER__
#define __SENDER__

#include "../../Common/thread.h"
#include "../../Common/blocking_queue.h"
#include "../../Common/socket.h"

class Sender: public Thread {
public:
    Sender(): sending(true){

    }

    void run() override;

    void send(int u);

    void stop();

private:
    bool sending;
    //Player& player;
    //Map_2d& map;

};

#endif