#include "Sender.h"
#include <iostream>
#include <unistd.h>

void Sender::stop(){
    sending=false;
}

void Sender::send(int i){
    clientsocket->send(4);
}


void Sender::run(){
    while(sending){
       // std::cout <<"Estoy enviando" << std::endl;
       // sleep(5);
    }
}