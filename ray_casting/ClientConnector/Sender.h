#ifndef __SENDER__
#define __SENDER__

#include "thread.h"

class Sender: public Thread {
public:
    Sender(): sending(true){

    }

    void run() override;

    void stop();

private:
    bool sending;
    //Player& player;
    //Map_2d& map;

};

#endif