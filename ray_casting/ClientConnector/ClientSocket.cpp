#include "ClientSocket.h"
#include <iostream>
#include <stdint.h>
#include "../../Common/protocol.h"
#include <inttypes.h>
 #include "yaml-cpp/yaml.h"

ClientSocket::ClientSocket(NonBlockingQueue<UpdateMessage*>& non_bloq_queue,const char* Host,const char* Port):\
recv_queue(non_bloq_queue),socket(Host,Port){
    YAML::Node data_config=YAML::LoadFile("../Yaml_configs/server_config.yaml");
    initial_lives=data_config["max_resurrections"].as<int>();;
}


void ClientSocket::close(){
    socket.shutdown();
    socket.close();
}
New_Player_Event ClientSocket::recv_player_func(){
    int bytes_received=0;
    uint32_t player_id[1];
    uint32_t map_size[1];
    uint32_t pos_x[1];
    uint32_t pos_y[1];
    float angle[1];
    uint32_t life[1];
    uint8_t resurrected[1];
    uint32_t treasure[1];
    uint32_t bullets[1];
    socket.receive((char*)player_id, sizeof(player_id),bytes_received);
    socket.receive((char*)map_size, sizeof(map_size),bytes_received);
    map_size[0]=le32toh(map_size[0]);
    int map_size_=int(map_size[0]);
    std::cout << "Map size es" << map_size_ << std::endl;
    char map[map_size_];
    //memset(map,0,map_size_);
    socket.receive(map, map_size_,bytes_received);
    std::cout << "Recibi bytes:" << bytes_received << std::endl;
    socket.receive((char*)pos_x,sizeof(pos_x),bytes_received);
    socket.receive((char*)pos_y,sizeof(pos_y),bytes_received);
    socket.receive((char*)angle,sizeof(angle),bytes_received);
    socket.receive((char*)life,sizeof(life),bytes_received);
    socket.receive((char*)resurrected,sizeof(resurrected),bytes_received);
    socket.receive((char*)treasure,sizeof(treasure),bytes_received);
    socket.receive((char*)bullets,sizeof(bullets),bytes_received);
    std::string map__(map);
    std::string map_final=map__.substr(0,map_size_);
    std::cout << "Map final es" << map_final << std::endl;
    player_id[0]=le32toh(player_id[0]);
    //map_len[0]=le32toh(map_len[0]);
    pos_x[0]=le32toh(pos_x[0]);
    pos_y[0]=le32toh(pos_y[0]);
    angle[0]=le32toh(angle[0]);
    life[0]=le32toh(life[0]);
    treasure[0]=le32toh(treasure[0]);
    resurrected[0]=le32toh(resurrected[0]);
    bullets[0]=le32toh(bullets[0]);
    std::cout << "recibi player id:" << unsigned(player_id[0])<< std::endl;
    std::cout << "recibi map:" << unsigned(map[0])<< std::endl;
    std::cout << "recibi posx:" << unsigned(pos_x[0])<< std::endl;
    std::cout << "recibi posy:" << unsigned(pos_y[0])<< std::endl;
    std::cout << "recibi angle:" << unsigned(angle[0])<< std::endl;
    std::cout << "recibi life:" << unsigned(life[0])<< std::endl;
    std::cout << "recibi treasure:" << unsigned(treasure[0])<< std::endl;
    std::cout << "recibi resurrected:" << unsigned(resurrected[0])<< std::endl;
    std::cout << "recibi bullets:" << unsigned(bullets[0])<< std::endl;
    my_player.player_id=player_id[0];
    //my_player.map=map[0];
    my_player.map=map_final;
    my_player.pos_x=pos_x[0];
    my_player.pos_y=pos_y[0];
    my_player.angle=angle[0];
    my_player.life=life[0];
    my_player.resurrected=initial_lives-resurrected[0];
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
        std::cout << "Empece a recibir" << std::endl;
        std::cout << "Opcode es" << unsigned(buffer[0]) << std::endl;
        std::cout << "Tipo de opcode es" << unsigned(buffer[1]) << std::endl;
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
                    update_message->load_new_player_event(new_player.player_id,\
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
                case SCORES_EV:{
                    std::cout<<"Entro a score ev"<<std::endl;
                    uint32_t num_players[1];
                    /*uint32_t name1_size[1];
                    uint32_t name2_size[1];
                    uint32_t name3_size[1];
                    uint32_t name4_size[1];
                    uint32_t name5_size[1];*/
                    uint32_t score1_size[1];
                    uint32_t score2_size[1];
                    uint32_t score3_size[1];
                    uint32_t score4_size[1];
                    uint32_t score5_size[1];

                    socket.receive((char*)num_players,sizeof(num_players),bytes_received);

                   // socket.receive((char*)name1_size,sizeof(name1_size),bytes_received);
                   /* name1_size[0]=le32toh(name1_size[0]);
                    int name1_size_=int(name1_size[0]);
                    std::cout << "Name 1 size es" << name1_size_ << std::endl;
                    char name1[name1_size_];*/
                    //memset(map,0,map_size_);
                   // socket.receive(name1, name1_size_,bytes_received);
                    socket.receive((char*)score1_size,sizeof(score1_size),bytes_received);
                    score1_size[0]=le32toh(score1_size[0]);

                    std::cout << "Score 1 es" << unsigned(score1_size[0]) << std::endl;
                    /*
                    std::string name1__(name1);
                    std::string name1_final=name1__.substr(0,name1_size_);
                    std::cout << "Name 1 es" << name1_final << std::endl;*/

                   // socket.receive((char*)name2_size,sizeof(name2_size),bytes_received);
                    /*name2_size[0]=le32toh(name2_size[0]);
                    int name2_size_=int(name2_size[0]);
                    std::cout << "Name 2 size es" << name2_size_ << std::endl;
                    char name2[name2_size_];*/
                    //memset(map,0,map_size_);
                    //socket.receive(name2, name2_size_,bytes_received);
                    socket.receive((char*)score2_size,sizeof(score2_size),bytes_received);
                    score2_size[0]=le32toh(score2_size[0]);
                    /*std::string name2__(name2);
                    std::string name2_final=name2__.substr(0,name2_size_);
                    std::cout << "Name 2 es" << name2_final << std::endl;*/
                    std::cout << "Score 2 es" << unsigned(score2_size[0]) << std::endl;

                   // socket.receive((char*)name3_size,sizeof(name3_size),bytes_received);
                    /*name3_size[0]=le32toh(name3_size[0]);
                    int name3_size_=int(name3_size[0]);
                    std::cout << "Name 3 size es" << name3_size_ << std::endl;
                    char name3[name3_size_];
                    //socket.receive(name3, name3_size_,bytes_received);*/
                    socket.receive((char*)score3_size,sizeof(score3_size),bytes_received);
                    score3_size[0]=le32toh(score3_size[0]);
                    /*std::string name3__(name1);
                    std::string name3_final=name3__.substr(0,name3_size_);
                    std::cout << "Name 3 es" << name3_final << std::endl;*/
                    std::cout << "Score 3 es" << unsigned(score3_size[0]) << std::endl;


                   // socket.receive((char*)name4_size,sizeof(name4_size),bytes_received);
                    //name4_size[0]=le32toh(name4_size[0]);
                    /*int name4_size_=int(name4_size[0]);
                    std::cout << "Name 4 size es" << name4_size_ << std::endl;
                    char name4[name4_size_];*/
                    //memset(map,0,map_size_);
                   // socket.receive(name4, name4_size_,bytes_received);
                    socket.receive((char*)score4_size,sizeof(score4_size),bytes_received);
                    score4_size[0]=le32toh(score4_size[0]);
                    /*std::string name4__(name4);
                    std::string name4_final=name4__.substr(0,name4_size_);
                    std::cout << "Name 4 es" << name4_final << std::endl;*/
                    std::cout << "Score 4 es" << unsigned(score4_size[0]) << std::endl;


                    //socket.receive((char*)name5_size,sizeof(name5_size),bytes_received);
                   /* name5_size[0]=le32toh(name5_size[0]);
                    int name5_size_=int(name5_size[0]);
                    std::cout << "Name 5 size es" << name5_size_ << std::endl;
                    char name5[name5_size_];*/
                    //memset(map,0,map_size_);
                    //socket.receive(name5, name5_size_,bytes_received);
                    socket.receive((char*)score5_size,sizeof(score5_size),bytes_received);
                    score5_size[0]=le32toh(score5_size[0]);
                    /*std::string name5__(name5);
                    std::string name5_final=name5__.substr(0,name5_size_);
                    std::cout << "Name 5 es" << name5_final << std::endl;*/
                    std::cout << "Score 5 es" << unsigned(score5_size[0]) << std::endl;
/*
                    //player 1
                    const char* char_name_1 = name_1.c_str();
                    uint32_t name_1_size[1];
                    name_1_size[0] = strlen(char_name_1);
                    name_1_size[0] = htole32(name_1_size[0]);
                    std::cout << "NAME_1: " << char_name_1 << std::endl;
                    std::cout << "NAME_1 SIZE: " << name_1_size << std::endl;
                    peer.send((char *)name_1_size, sizeof(name_1_size));
                    peer.send(char_name_1, sizeof(char_name_1));
                    this->score_1 = htole32(this->score_1);
                    peer.send((char *)&score_1, sizeof(score_1));
                    //player 2
                    const char* char_name_2 = name_2.c_str();
                    uint32_t name_2_size[1];
                    name_2_size[0] = strlen(char_name_2);
                    name_2_size[0] = htole32(name_2_size[0]);
                    std::cout << "NAME_2: " << char_name_2 << std::endl;
                    std::cout << "NAME_2 SIZE: " << name_2_size << std::endl;
                    peer.send((char *)name_2_size, sizeof(name_2_size));
                    peer.send(char_name_2, sizeof(char_name_2));
                    this->score_2 = htole32(this->score_2);
                    peer.send((char *)&score_2, sizeof(score_2));
                    //player 3
                    const char* char_name_3 = name_3.c_str();
                    uint32_t name_3_size[1];
                    name_3_size[0] = strlen(char_name_3);
                    name_3_size[0] = htole32(name_3_size[0]);
                    std::cout << "NAME_3: " << char_name_3 << std::endl;
                    std::cout << "NAME_3 SIZE: " << name_3_size << std::endl;
                    peer.send((char *)name_3_size, sizeof(name_3_size));
                    peer.send(char_name_3, sizeof(char_name_3));
                    this->score_3= htole32(this->score_3);
                    peer.send((char *)&score_3, sizeof(score_3));
                    //player 4
                    const char* char_name_4 = name_4.c_str();
                    uint32_t name_4_size[1];
                    name_4_size[0] = strlen(char_name_4);
                    name_4_size[0] = htole32(name_4_size[0]);
                    std::cout << "NAME_4: " << char_name_4 << std::endl;
                    std::cout << "NAME_4 SIZE: " << name_4_size << std::endl;
                    peer.send((char *)name_4_size, sizeof(name_4_size));
                    peer.send(char_name_4, sizeof(char_name_4));
                    this->score_4 = htole32(this->score_4);
                    peer.send((char *)&score_4, sizeof(score_4));
                    //player 5
                    const char* char_name_5 = name_5.c_str();
                    uint32_t name_5_size[1];
                    name_5_size[0] = strlen(char_name_5);
                    name_5_size[0] = htole32(name_5_size[0]);
                    std::cout << "NAME_5: " << char_name_5 << std::endl;
                    std::cout << "NAME_5 SIZE: " << name_5_size << std::endl;
                    peer.send((char *)name_5_size, sizeof(name_5_size));
                    peer.send(char_name_5, sizeof(char_name_5));
                    this->score_5= htole32(this->score_5);
                    peer.send((char *)&score_5, sizeof(score_5));
*/

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
