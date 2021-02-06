#include "Receiver.h"
#include <unistd.h>

void Receiver::stop(){
    receiving=false;
    clientsocket->close();
}


void Receiver::run(){
    try{
        while(receiving){
            uint8_t buffer[2];  //DESCOMENTAR
            clientsocket->recv((char*)buffer,2);  //DESCOMENTAR
        }
    }
    catch(...){}
}