#include "Sender.h"
#include <iostream>
#include <unistd.h>
#include <stdint.h>

void Sender::stop(){
    //std::cout << "Stopie" << std::endl;
    sending=false;
}

void Sender::run(){
    while(sending){
        try{
            Command* command=SendQueue.pop();
            if(command){
                clientsocket->send(command->get_opcode());
                //std::cout << "Opcode popeado:" << unsigned(command->get_opcode()) << std::endl;
            }
        }
        catch(...){}
    }
}