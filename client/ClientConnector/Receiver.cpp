#include "Receiver.h"
#include <unistd.h>

void Receiver::stop(){
    receiving=false;
    clientsocket->close();
}


void Receiver::run(){
    try{
        while(receiving){
            uint8_t buffer[2];  
            clientsocket->recv((char*)buffer,2);  
        }
    }
    catch(...){}
}