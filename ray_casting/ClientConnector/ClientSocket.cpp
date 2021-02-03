#include "ClientSocket.h"
#include <iostream>
#include <stdint.h>
#include "../../Common/protocol.h"

ClientSocket::ClientSocket():socket("127.0.0.1","8080"){
   // Socket socket("127.0.0.1","8080");
    
}


int ClientSocket::recv(){
    return 2;
}

void ClientSocket::send(uint8_t msg){
    uint8_t opcode=1;
    //uint8_t opcode=START_MOVING_UP_CMD;
    //char opcode_enviar=(char) opcode;     El posta(descomentar)
   // char buff1[2]="1";
   // char* opcode=1;
    std::cout << "Envio por socket: Comando:" << unsigned(opcode) << "Tipo de comando:" << unsigned(msg) << std::endl;
    //std::cout << "Envio" << msg << std::endl;
    //const char* opcode_char= (char*) opcode;
    //const char* command_type= (char*) msg;
    //socket.send(opcode_char, 1);
    //socket.send(command_type, 1);
    //socket.send((char*)opcode, 1);
    //socket.send(&opcode_enviar,1);    El posta(descomentar)
    //socket.send(command_type, 1);
}
