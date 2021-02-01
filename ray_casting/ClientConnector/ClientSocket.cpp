#include "ClientSocket.h"
#include <iostream>


ClientSocket::ClientSocket(){
    Socket socket("127.0.0.1","8080");
    
}


int ClientSocket::recv(){
    return 2;
}

void ClientSocket::send(int msg){

    //std::cout << "Envio" << msg << std::endl;

}
