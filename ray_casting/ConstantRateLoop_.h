#ifndef LOOP_H
#define LOOP_H

#include "Client.h"
#include "Player_handler.h"
#include "ClientConnector/ReceiveController.h"



class ConstantRateLoop_{
private:
    bool is_running;
    int rate;
    Player_handler& player_handler;
    Client& client;
    ReceiveController& receive_controller;


    public:
        ConstantRateLoop_(Player_handler& Player_Handler,Client& Client,\
        ReceiveController& Receive_Controller);
        //~ConstantRateLoop_();
        void run();
};

#endif