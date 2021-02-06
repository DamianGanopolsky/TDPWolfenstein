#include "Sender.h"
#include <iostream>
#include <unistd.h>
#include <stdint.h>

void Sender::stop(){
    std::cout << "Stopie" << std::endl;
    sending=false;
}
/*
void Sender::send(int i){
    clientsocket->send(4);
}

*/
void Sender::run(){
    while(sending){
        try{
            std::cout << "Entre" << std::endl;
            Command* command=SendQueue.pop();
            std::cout << "Sali" << std::endl;
            //if(command->get_opcode()==)
            if(command){
                clientsocket->send(command->get_opcode());
                std::cout << "Opcode popeado:" << unsigned(command->get_opcode()) << std::endl;
            }

        }
        catch(...){
            std::cout << "Exceopm" << std::endl;
        }
        std::cout <<"Estoy enviando" << std::endl;
    }
}