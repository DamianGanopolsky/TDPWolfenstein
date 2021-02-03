#include "ClientSocket.h"
#include <iostream>
#include <stdint.h>
#include "../../Common/protocol.h"

ClientSocket::ClientSocket():socket("127.0.0.1","8082"){
   // Socket socket("127.0.0.1","8080");
    
}




int ClientSocket::recv(char* recv_buff,int len){
    int bytes_received=0;
    socket.receive(recv_buff,2,bytes_received);
    
    return 2;
}

void ClientSocket::send(uint8_t msg){
    uint8_t opcode=128;
    //uint8_t opcode=START_MOVING_UP_CMD;
    uint8_t buffer[2];
    buffer[0] = opcode;
    buffer[1] = msg;
    //char opcode_enviar=(char) opcode;    
   // char buff1[2]="1";
   // char* opcode=1;
    std::cout << "Envio por socket: Comando:" << unsigned(opcode) << "Tipo de comando:" << unsigned(msg) << std::endl;
    //std::cout << "Envio" << msg << std::endl;
    //const char* opcode_char= (char*) opcode;
    //const char* command_type= (char*) msg;
    //socket.send(opcode_char, 1);
    //socket.send(command_type, 1);
    //socket.send((char*)opcode, 1);
    //socket.send(&opcode_enviar,1); 
    //socket.send(command_type, 1);
    socket.send((char*)buffer, 2);
}
