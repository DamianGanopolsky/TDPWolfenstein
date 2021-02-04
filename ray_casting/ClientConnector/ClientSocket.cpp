#include "ClientSocket.h"
#include <iostream>
#include <stdint.h>
#include "../../Common/protocol.h"

ClientSocket::ClientSocket():socket("127.0.0.1","8082"){
}




int ClientSocket::recv(char* recv_buff,int len){
    int bytes_received=0;
    socket.receive(recv_buff,2,bytes_received);
    uint8_t buffer[2];
    buffer[0]=*recv_buff;
    buffer[1]=*(recv_buff+1);
    //buffer[]
    
    std::cout << "recibi" << unsigned(buffer[0]) << "siguiente:" << unsigned(buffer[1]) << std::endl;
    switch(buffer[1]){
        case NEW_PLAYER_EV: {         
            uint8_t buffer2[1];
            socket.receive((char*)buffer2,1,bytes_received);
            //uint32_t play_id;

            std::cout << "recibi el id:" << unsigned(buffer2[0])<< std::endl;
           // uint8_t buffer2[1];
            socket.receive((char*)buffer2,1,bytes_received);
           // uint8_t buffer2[1];
            socket.receive((char*)buffer2,1,bytes_received);
           // uint8_t buffer2[1];
            socket.receive((char*)buffer2,1,bytes_received);
            //uint8_t buffer2[1];
            socket.receive((char*)buffer2,1,bytes_received);
            //uint8_t buffer2[1];
            socket.receive((char*)buffer2,1,bytes_received);
            std::cout << "recibi el id:" << unsigned(buffer2[0])<< std::endl;
            //uint8_t buffer2[1];
           // socket.receive((char*)buffer2,1,bytes_received);
            //uint8_t buffer2[1];
            //socket.receive((char*)buffer2,1,bytes_received);
            /*this->map = htole32(this->map);
            peer.send((char *)&map, sizeof(map));
            this->pos_x = htole32(this->pos_x);
            this->pos_y = htole32(this->pos_y);
            peer.send((char *)&pos_x, sizeof(pos_x));
            peer.send((char *)&pos_y, sizeof(pos_y));
            peer.send((char *)&angle, sizeof(angle));
            peer.send((char *)&life, sizeof(life));
            peer.send((char *)&resurrected, sizeof(resurrected));
            peer.send((char *)&treasure, sizeof(treasure));
            peer.send((char *)&bullets, sizeof(bullets));*/
            break;
        }
    }
    return 2;
}

void ClientSocket::send(uint8_t msg){
    uint8_t opcode=128;
    //uint8_t opcode=START_MOVING_UP_CMD;
    std::cout << "awsd"  << std::endl;
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
