#include "ClientSocket.h"
#include <iostream>
#include <stdint.h>
#include "../../Common/protocol.h"
#include <inttypes.h>

ClientSocket::ClientSocket(NonBlockingQueue<UpdateMessage*>& non_bloq_queue):\
recv_queue(non_bloq_queue),socket("127.0.0.1","8082"){
}




int ClientSocket::recv(char* recv_buff,int len){
    int bytes_received=0;
    socket.receive(recv_buff,2,bytes_received);
    uint8_t buffer[2];
    buffer[0]=*recv_buff;
    buffer[1]=*(recv_buff+1);
    //buffer[]
    UpdateMessage* update_message = new UpdateMessage(buffer[0],buffer[1]);
    std::cout << "recibi" << unsigned(buffer[0]) << "siguiente:" << unsigned(buffer[1]) << std::endl;
    switch(buffer[1]){
        case NEW_PLAYER_EV: {         
            uint8_t player_id[1];
            socket.receive((char*)player_id,1,bytes_received);
            uint8_t map[1];

            std::cout << "recibi el id:" << unsigned(player_id[0])<< std::endl;
           // uint8_t buffer2[1];
            socket.receive((char*)map,1,bytes_received);
            uint32_t pos_x[1];
            uint32_t pos_y[1];
            //float angle;
            uint32_t angle[1];
            uint32_t life[1];
            uint8_t resurrected[1];
            uint32_t treasure[1];
            uint32_t bullets[1];
           // uint8_t buffer2[1];
            socket.receive((char*)pos_x,4,bytes_received);
           // uint8_t buffer2[1];
            socket.receive((char*)pos_y,4,bytes_received);
            //uint8_t buffer2[1];
            socket.receive((char*)angle,1,bytes_received);
            //uint8_t buffer2[1];
            socket.receive((char*)life,4,bytes_received);
            //std::cout << "life aca es" << unsigned(life[0]) << std::endl;
            printf("%" PRIu32 "\n",life[0]);
            //std::cout << "recibi el id:" << unsigned(buffer2[0])<< std::endl;
            //uint8_t buffer2[1];
            socket.receive((char*)resurrected,1,bytes_received);
            //uint8_t buffer2[1];
            socket.receive((char*)treasure,1,bytes_received);
            socket.receive((char*)bullets,1,bytes_received);
            update_message->load_new_player_event(player_id[0],map[0],pos_x[0],pos_y[0],angle[0],life[0]\
            ,resurrected[0],treasure[0],bullets[0]);
            recv_queue.push(std::move(update_message));
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
