#include "Sender.h"
#include <iostream>
#include <unistd.h>
#include <stdint.h>

void Sender::stop(){
    sending=false;
}

void Sender::run(){
    while(sending){
        try{
            Command* command=SendQueue.pop();
            if(command){
                clientsocket->send(command->get_opcode());
            }
        }
        catch(...){
            std::cerr << "Send queue closed" << std::endl;
        }
    }
}