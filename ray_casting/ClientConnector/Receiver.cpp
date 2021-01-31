#include "Receiver.h"
#include <unistd.h>

void Receiver::stop(){
    receiving=false;
}


void Receiver::run(){
    while(receiving){
        std::cout <<"Estoy recibiendo" << std::endl;
        sleep(5);
    }
}