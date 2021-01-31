#include "Sender.h"
#include <iostream>
#include <unistd.h>

void Sender::stop(){
    sending=false;
}


void Sender::run(){
    while(sending){
        std::cout <<"Estoy enviando" << std::endl;
        sleep(5);
    }
}