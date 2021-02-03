#include "Receiver.h"
#include <unistd.h>

void Receiver::stop(){
    receiving=false;
}


void Receiver::run(){
    while(receiving){
        //recv_queue.push()
    }
}