#include "Receiver.h"
#include <unistd.h>

void Receiver::stop(){
    receiving=false;
}


void Receiver::run(){
    while(receiving){
        //recv_queue.push()
        //int bytes_received = 0;
		//uint8_t buffer[2];
        
        std::cout << "Empiezo a recibir" << std::endl;
        sleep(20);
        //bytes_received=clientsocket->recv((char*)buffer,2);
        //std::cout << bytes_received << std::endl;
        //while (peer.receive((char *)buffer, 2, bytes_received))
    }
}