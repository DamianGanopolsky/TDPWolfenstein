#include "ClientSocket.h"
#include <iostream>
#include <stdint.h>
#include "../../Common/protocol.h"
#include <inttypes.h>

ClientSocket::ClientSocket(NonBlockingQueue<UpdateMessage*>& non_bloq_queue,const char* Host,const char* Port):\
recv_queue(non_bloq_queue),socket(Host,Port){
}


void ClientSocket::close(){
    socket.shutdown();
    socket.close();
}
New_Player_Event ClientSocket::recv_player_func(){
    int bytes_received=0;
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
    socket.receive((char*)pos_y,sizeof(pos_y),bytes_received);
    socket.receive((char*)angle,sizeof(angle),bytes_received);
    socket.receive((char*)life,sizeof(life),bytes_received);
    socket.receive((char*)resurrected,sizeof(resurrected),bytes_received);
    socket.receive((char*)treasure,sizeof(treasure),bytes_received);
    socket.receive((char*)bullets,sizeof(bullets),bytes_received);
    
    player_id[0]=le32toh(player_id[0]);
    map[0]=le32toh(map[0]);
    pos_x[0]=le32toh(pos_x[0]);
    pos_y[0]=le32toh(pos_y[0]);
    angle[0]=le32toh(angle[0]);
    life[0]=le32toh(life[0]);
    treasure[0]=le32toh(treasure[0]);
    resurrected[0]=le32toh(resurrected[0]);
    bullets[0]=le32toh(bullets[0]);
   /* std::cout << "recibi player id:" << unsigned(player_id[0])<< std::endl;
    std::cout << "recibi map:" << unsigned(map[0])<< std::endl;
    std::cout << "recibi posx:" << unsigned(pos_x[0])<< std::endl;
    std::cout << "recibi posy:" << unsigned(pos_y[0])<< std::endl;
    std::cout << "recibi angle:" << unsigned(angle[0])<< std::endl;
    std::cout << "recibi life:" << unsigned(life[0])<< std::endl;
    std::cout << "recibi treasure:" << unsigned(treasure[0])<< std::endl;
    std::cout << "recibi resurrected:" << unsigned(resurrected[0])<< std::endl;
    std::cout << "recibi bullets:" << unsigned(bullets[0])<< std::endl;*/
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

New_Player_Event ClientSocket::recv_player(){
    int bytes_received=0;
    uint8_t buffer[2];
    socket.receive((char*)buffer,sizeof(buffer),bytes_received);
    my_player = recv_player_func();
    return my_player;
}


void ClientSocket::recv(char* recv_buff,int len){
    int bytes_received=0;
    
    try{
        //socket.receive(recv_buff,2,bytes_received);
        uint8_t buffer[2];
       // buffer[0]=*recv_buff;
       // buffer[1]=*(recv_buff+1);
        socket.receive((char*)buffer,sizeof(buffer),bytes_received);
        /*std::cout << "Empece a recibir" << std::endl;
        std::cout << "OPcode es" << unsigned(buffer[0]) << std::endl;
        std::cout << "Tipo de opcode es" << unsigned(buffer[1]) << std::endl;*/
        UpdateMessage* update_message = new UpdateMessage(buffer[0],buffer[1]);
        if(buffer[0]==EVENT_OPCODE){  
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
                    player_id[0]=le32toh(player_id[0]);
                    pos_x[0]=le32toh(pos_x[0]);
                    pos_y[0]=le32toh(pos_y[0]);
                    angle[0]=le32toh(angle[0]);
                    /*std::cout << "REcibi player id:" << player_id[0] << std::endl;
                    std::cout << "REcibi pos x:" << pos_x[0] << std::endl;
                    std::cout << "REcibi pos y:" << pos_y[0] << std::endl;
                    std::cout << "REcibi angulo:" << angle[0] << std::endl;*/
                    update_message->load_movement_event(player_id[0],pos_x[0],pos_y[0],angle[0],\
                    is_moving[0],is_shooting[0]);
                    recv_queue.push(std::move(update_message));
                    break;
                }
                case RESURRECT_EV:
                case NEW_PLAYER_EV: {                         
                    New_Player_Event new_player=recv_player_func();
                    update_message->load_new_player_event(new_player.player_id,new_player.map,\
                    new_player.pos_x,new_player.pos_y,new_player.angle,new_player.life\
                    ,new_player.resurrected,new_player.score,new_player.bullets);
                    recv_queue.push(std::move(update_message));
                    break;
                }
                case ATTACK_EV:{
                    uint32_t player_id[1];
                    uint32_t value[1];
                    socket.receive((char*)player_id,sizeof(player_id),bytes_received);
                    socket.receive((char*)value,sizeof(value),bytes_received);
                    player_id[0]=le32toh(player_id[0]);
                    value[0]=le32toh(value[0]);
                    /*std::cout << "Recibi player id:" << player_id[0] << std::endl;
                    std::cout << "Recibi value:" << value[0] << std::endl;*/
                    update_message->load_changed_stat(player_id[0],value[0]);
                    recv_queue.push(std::move(update_message));
                    break;
                }
                case BE_ATTACKED_EV:
                case CHANGE_WEAPON_EV:{
                    uint32_t player_id[1];
                    uint32_t value[1];
                    socket.receive((char*)player_id,sizeof(player_id),bytes_received);
                    socket.receive((char*)value,sizeof(value),bytes_received);
                    player_id[0]=le32toh(player_id[0]);
                    value[0]=le32toh(value[0]);
                    update_message->load_changed_stat(player_id[0],value[0]);
                    recv_queue.push(std::move(update_message));
                    break;
                }
                case DEATH_EV:{
                    uint32_t player_id[1];
                    uint32_t pos_x[1];
                    uint32_t pos_y[1];
                    socket.receive((char*)player_id,sizeof(player_id),bytes_received);
                    socket.receive((char*)pos_x,sizeof(pos_x),bytes_received);
                    socket.receive((char*)pos_y,sizeof(pos_y),bytes_received);
                    player_id[0]=le32toh(player_id[0]);
                    pos_x[0]=le32toh(pos_x[0]);
                    pos_y[0]=le32toh(pos_y[0]);
                    update_message->load_death_event(player_id[0],pos_x[0],pos_y[0]);
                    recv_queue.push(std::move(update_message));
                    break;
                }
            }
        }
        if(buffer[0]==ITEM_CHANGED_OPCODE){
            switch(buffer[1]){
                case CLOSE_DOOR_ITM:
                case OPEN_DOOR_ITM:
                    uint32_t pos_x[1];
                    uint32_t pos_y[1];
                    socket.receive((char*)pos_x, sizeof(pos_x),bytes_received);
                    socket.receive((char*)pos_y, sizeof(pos_y),bytes_received);
                    pos_x[0]=le32toh(pos_x[0]);
                    pos_y[0]=le32toh(pos_y[0]);
                    update_message->load_door_changed(pos_x[0],pos_y[0]);
                    recv_queue.push(std::move(update_message));
                    break;
                case WEAPON_TAKEN_ITM:{
                    uint32_t player_id[1];
                    uint32_t pos_x[1];
                    uint32_t pos_y[1];
                    uint32_t value[1];
                    value[0]=54;
                    socket.receive((char*)player_id,sizeof(player_id),bytes_received);
                    socket.receive((char*)pos_x, sizeof(pos_x),bytes_received);
                    socket.receive((char*)pos_y, sizeof(pos_y),bytes_received);
                    player_id[0]=le32toh(player_id[0]);
                    pos_x[0]=le32toh(pos_x[0]);
                    pos_y[0]=le32toh(pos_y[0]);
                    update_message->load_item_taken(player_id[0],pos_x[0],pos_y[0],value[0]);
                    recv_queue.push(std::move(update_message));
                    break;
                }
                case MEDICAL_KIT_TAKEN_ITM:
                case FOOD_TAKEN_ITM:
                case BLOOD_TAKEN_ITM:
                case KEY_TAKEN_ITM:
                case TREASURE_TAKEN_ITM:
                case BULLETS_TAKEN_ITM:{
                    uint32_t player_id[1];
                    uint32_t pos_x[1];
                    uint32_t pos_y[1];
                    uint32_t value[1];
                    socket.receive((char*)player_id,sizeof(player_id),bytes_received);
                    socket.receive((char*)pos_x, sizeof(pos_x),bytes_received);
                    socket.receive((char*)pos_y, sizeof(pos_y),bytes_received);
                    socket.receive((char*)value, sizeof(value),bytes_received);
                    player_id[0]=le32toh(player_id[0]);
                    pos_x[0]=le32toh(pos_x[0]);
                    pos_y[0]=le32toh(pos_y[0]);
                    value[0]=le32toh(value[0]);
                    std::cout << "Pos x es" << pos_x[0] << "Pos y es" << pos_y[0] << std::endl;
                    update_message->load_item_taken(player_id[0],pos_x[0],pos_y[0],value[0]);
                    recv_queue.push(std::move(update_message));
                    break;
                }
                default:
                    throw Exception("Unknown item type.");
                    break;
            }
        }
        //std::cout << "Termine de recibir" << std::endl;
    }
    catch(...){}
}

void ClientSocket::send(uint8_t msg){
    uint8_t opcode=128;
    uint8_t buffer[2];
    buffer[0] = opcode;
    buffer[1] = msg;
    //std::cout << "Envio por socket: Comando:" << unsigned(opcode) << "Tipo de comando:" << unsigned(msg) << std::endl;
    socket.send((char*)buffer, 2);
}
