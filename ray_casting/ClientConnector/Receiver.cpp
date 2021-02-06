#include "Receiver.h"
#include <unistd.h>

void Receiver::stop(){
    receiving=false;
    clientsocket->close();
}


void Receiver::run(){
    //uint8_t buffer[2];
    //New_Player_Event my_player=clientsocket->recv_player((char*)buffer);
    //recv_controller.InitializeClient(my_player);
    try{
        while(receiving){
            //int bytes_received = 0; //DESCOMENTAR
            uint8_t buffer[2];  //DESCOMENTAR
            std::cout << "Empece a recibir" << std::endl;
            clientsocket->recv((char*)buffer,2);  //DESCOMENTAR
        }
    }
    catch(...){
        std::cout << "Termino receiver run" << std::endl;
    }

}