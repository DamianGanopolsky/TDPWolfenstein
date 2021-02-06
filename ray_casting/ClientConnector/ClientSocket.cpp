#include "ClientSocket.h"
#include <iostream>
#include <stdint.h>
#include "../../Common/protocol.h"
#include <inttypes.h>

ClientSocket::ClientSocket(NonBlockingQueue<UpdateMessage*>& non_bloq_queue):\
recv_queue(non_bloq_queue),socket("127.0.0.1","8082"){
}


void ClientSocket::close(){
    socket.shutdown();
    socket.close();
}


New_Player_Event ClientSocket::recv_player(){
    int bytes_received=0;
    uint8_t buffer[2];
    socket.receive((char*)buffer,sizeof(buffer),bytes_received);
    uint32_t player_id[1];
    uint32_t map[1];
    uint32_t pos_x[1];
    uint32_t pos_y[1];
    float angle[1];
    uint32_t life[1];
    uint8_t resurrected[1];
    uint32_t treasure[1];
    uint32_t bullets[1];
    socket.receive((char*)player_id, sizeof(player_id),bytes_received);
    socket.receive((char*)map, sizeof(map),bytes_received);
    socket.receive((char*)pos_x,sizeof(pos_x),bytes_received);
    std::cout << "recibi posx:" << unsigned(pos_x[0])<< std::endl;
    socket.receive((char*)pos_y,sizeof(pos_y),bytes_received);
    std::cout << "recibi posy:" << unsigned(pos_y[0])<< std::endl;
    socket.receive((char*)angle,sizeof(angle),bytes_received);
    std::cout << "recibi angle:" << unsigned(angle[0])<< std::endl;
    socket.receive((char*)life,sizeof(life),bytes_received);
    std::cout << "recibi life:" << unsigned(life[0])<< std::endl;
    socket.receive((char*)resurrected,sizeof(resurrected),bytes_received);
    socket.receive((char*)treasure,sizeof(treasure),bytes_received);
    socket.receive((char*)bullets,sizeof(bullets),bytes_received);
    std::cout << "recibi bullets:" << unsigned(bullets[0])<< std::endl;
    my_player.player_id=player_id[0];
    my_player.map=map[0];
    my_player.pos_x=pos_x[0];
    my_player.pos_y=pos_y[0];
    my_player.angle=angle[0];
    my_player.life=life[0];
    my_player.resurrected=resurrected[0];
    my_player.score=treasure[0];
    my_player.bullets=bullets[0];
    return my_player;
}


void ClientSocket::recv(char* recv_buff,int len){
    int bytes_received=0;
    try{
        socket.receive(recv_buff,2,bytes_received);
        uint8_t buffer[2];
        buffer[0]=*recv_buff;
        buffer[1]=*(recv_buff+1);
        UpdateMessage* update_message = new UpdateMessage(buffer[0],buffer[1]);
        switch(buffer[1]){

            case MOVEMENT_EV:{
                uint32_t player_id[1];
                socket.receive((char*)player_id, sizeof(player_id),bytes_received);
                
                uint32_t pos_x[1];
                socket.receive((char*)pos_x, sizeof(pos_x),bytes_received);
                uint32_t pos_y[1];
                socket.receive((char*)pos_y, sizeof(pos_y),bytes_received);
                float angle[1];
                socket.receive((char*)angle, sizeof(angle),bytes_received);
                uint8_t is_moving[1];
                socket.receive((char*)is_moving, sizeof(is_moving),bytes_received);
                uint8_t is_shooting[1];
                socket.receive((char*)is_shooting, sizeof(is_shooting),bytes_received);
                update_message->load_movement_event(player_id[0],pos_x[0],pos_y[0],angle[0],\
                is_moving[0],is_shooting[0]);
                recv_queue.push(std::move(update_message));

                break;
            }

            case NEW_PLAYER_EV: {         
                uint32_t player_id[1];
                socket.receive((char*)player_id, sizeof(player_id),bytes_received);
                uint32_t map[1];

                std::cout << "recibi el id:" << unsigned(player_id[0])<< std::endl;
            // uint8_t buffer2[1];
                socket.receive((char*)map, sizeof(map),bytes_received);
                //std::cout << "recibi el map:" << unsigned(map[0])<< std::endl;
                uint32_t pos_x[1];
                uint32_t pos_y[1];
                float angle[1];
                //uint32_t angle[1];
                uint32_t life[1];
                uint8_t resurrected[1];
                uint32_t treasure[1];
                uint32_t bullets[1];
            // uint8_t buffer2[1];
                socket.receive((char*)pos_x,sizeof(pos_x),bytes_received);
                std::cout << "recibi posx:" << unsigned(pos_x[0])<< std::endl;
            // uint8_t buffer2[1];
                socket.receive((char*)pos_y,sizeof(pos_y),bytes_received);
                std::cout << "recibi posy:" << unsigned(pos_y[0])<< std::endl;
                //uint8_t buffer2[1];
                socket.receive((char*)angle,sizeof(angle),bytes_received);
                std::cout << "recibi angle:" << unsigned(angle[0])<< std::endl;
                //uint8_t buffer2[1];
                socket.receive((char*)life,sizeof(life),bytes_received);
                std::cout << "recibi life:" << unsigned(life[0])<< std::endl;
                std::cout << "life aca es" << unsigned(life[0]) << std::endl;
                //printf("%" PRIu32 "\n",life[0]);
                //uint8_t buffer2[1];
                socket.receive((char*)resurrected,sizeof(resurrected),bytes_received);
                std::cout << "recibi resurrected:" << unsigned(resurrected[0])<< std::endl;
                //uint8_t buffer2[1];
                socket.receive((char*)treasure,sizeof(treasure),bytes_received);
                std::cout << "recibi treasure:" << unsigned(treasure[0])<< std::endl;
                socket.receive((char*)bullets,sizeof(bullets),bytes_received);
                std::cout << "recibi bullets:" << unsigned(bullets[0])<< std::endl;
                update_message->load_new_player_event(player_id[0],map[0],pos_x[0],pos_y[0],angle[0],life[0]\
                ,resurrected[0],treasure[0],bullets[0]);
                recv_queue.push(std::move(update_message));
                break;
            }
            case CHANGE_WEAPON_EV:{
                uint32_t player_id[1];
                uint32_t weapon[1];
                socket.receive((char*)player_id, sizeof(player_id),bytes_received);
                socket.receive((char*)weapon, sizeof(weapon),bytes_received);
                update_message->load_changed_weapon(player_id[0],weapon[0]);
                recv_queue.push(std::move(update_message));
                break;
            }

        }
        std::cout << "Termine de recibir" << std::endl;
    }
    catch(...){
        //recv_queue.close();
        std::cout << "Termine" << std::endl;
    }
}

void ClientSocket::send(uint8_t msg){
    uint8_t opcode=128;
    uint8_t buffer[2];
    buffer[0] = opcode;
    buffer[1] = msg;
    std::cout << "Envio por socket: Comando:" << unsigned(opcode) << "Tipo de comando:" << unsigned(msg) << std::endl;
    socket.send((char*)buffer, 2);
}
