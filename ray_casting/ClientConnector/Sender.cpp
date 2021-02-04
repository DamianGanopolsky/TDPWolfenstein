#include "Sender.h"
#include <iostream>
#include <unistd.h>
#include <stdint.h>

void Sender::stop(){
    sending=false;
}
/*
void Sender::send(int i){
    clientsocket->send(4);
}

*/
void Sender::run(){
    while(sending){
        Command* command=SendQueue.pop();
        clientsocket->send(command->get_opcode());
        std::cout << "Opcode popeado:" << unsigned(command->get_opcode()) << std::endl;
        
        
       // std::cout <<"Estoy enviando" << std::endl;
       // sleep(5);
    }
}