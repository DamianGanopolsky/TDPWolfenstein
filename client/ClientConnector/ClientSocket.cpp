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

void ClientSocket::send_nickname(std::string NickName){
    int len_NickName=NickName.length();
    char nickname[len_NickName];
    strcpy(nickname, NickName.c_str());
    uint32_t nicknamesize[1];
    nicknamesize[0]=strlen(nickname);
    nicknamesize[0] = htole32(nicknamesize[0]);
    socket.send((char*)nicknamesize, sizeof(nicknamesize));
    socket.send(nickname,sizeof(nickname));
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
    char map[map_size_];
    socket.receive(map, map_size_,bytes_received);
    socket.receive((char*)pos_x,sizeof(pos_x),bytes_received);
    socket.receive((char*)pos_y,sizeof(pos_y),bytes_received);
    socket.receive((char*)angle,sizeof(angle),bytes_received);
    socket.receive((char*)life,sizeof(life),bytes_received);
    socket.receive((char*)resurrected,sizeof(resurrected),bytes_received);
    socket.receive((char*)treasure,sizeof(treasure),bytes_received);
    socket.receive((char*)bullets,sizeof(bullets),bytes_received);
    std::string map__(map);
    std::string map_final=map__.substr(0,map_size_);
    player_id[0]=le32toh(player_id[0]);
    pos_x[0]=le32toh(pos_x[0]);
    pos_y[0]=le32toh(pos_y[0]);
    angle[0]=le32toh(angle[0]);
    life[0]=le32toh(life[0]);
    treasure[0]=le32toh(treasure[0]);
    resurrected[0]=le32toh(resurrected[0]);
    bullets[0]=le32toh(bullets[0]);
    my_player.player_id=player_id[0];
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
        uint8_t buffer[2];
        socket.receive((char*)buffer,sizeof(buffer),bytes_received);
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
                    uint32_t num_players[1];
                    uint32_t score1_size[1];
                    uint32_t score2_size[1];
                    uint32_t score3_size[1];
                    uint32_t score4_size[1];
                    uint32_t score5_size[1];

                    uint32_t score1_final[1];
                    uint32_t score2_final[1];
                    uint32_t score3_final[1];
                    uint32_t score4_final[1];
                    uint32_t score5_final[1];

                    uint32_t kills1_final[1];
                    uint32_t kills2_final[1];
                    uint32_t kills3_final[1];
                    uint32_t kills4_final[1];
                    uint32_t kills5_final[1];

                    socket.receive((char*)num_players,sizeof(num_players),bytes_received);
                    uint32_t name1_size[1];
                    uint32_t name2_size[1];
                    uint32_t name3_size[1];
                    uint32_t name4_size[1];
                    uint32_t name5_size[1];
                    socket.receive((char*)name1_size,sizeof(name1_size),bytes_received);
                    name1_size[0]=le32toh(name1_size[0]);
                    int name1_size_=int(name1_size[0]);
                    char name1[name1_size_];
                    socket.receive(name1, name1_size_,bytes_received);

                    socket.receive((char*)score1_final,sizeof(score1_final),bytes_received);
                    score1_final[0]=le32toh(score1_final[0]);

                    socket.receive((char*)kills1_final,sizeof(kills1_final),bytes_received);
                    kills1_final[0]=le32toh(kills1_final[0]);


                    socket.receive((char*)score1_size,sizeof(score1_size),bytes_received);
                    score1_size[0]=le32toh(score1_size[0]);
                    
                    std::vector<Player_stats> pl_stats;


                    std::string name1__(name1);
                    std::string name1_final=name1__.substr(0,name1_size_);

                    Player_stats player_1;
                    player_1.Nickname=name1_final;
                    player_1.score=score1_size[0];
                    player_1.final_score=score1_final[0];
                    player_1.kills=kills1_final[0];
                    pl_stats.push_back(player_1);


                    socket.receive((char*)name2_size,sizeof(name2_size),bytes_received);
                    name2_size[0]=le32toh(name2_size[0]);
                    int name2_size_=int(name2_size[0]);
                    char name2[name2_size_];
                    socket.receive(name2, name2_size_,bytes_received);


                    socket.receive((char*)score2_final,sizeof(score2_final),bytes_received);
                    score2_final[0]=le32toh(score2_final[0]);

                    socket.receive((char*)kills2_final,sizeof(kills2_final),bytes_received);
                    kills2_final[0]=le32toh(kills2_final[0]);


                    socket.receive((char*)score2_size,sizeof(score2_size),bytes_received);
                    score2_size[0]=le32toh(score2_size[0]);

                    std::string name2__(name2);
                    std::string name2_final=name2__.substr(0,name2_size_);
                    Player_stats player_2;
                    player_2.Nickname=name2_final;
                    player_2.score=score2_size[0];
                    player_2.final_score=score2_final[0];
                    player_2.kills=kills2_final[0];
                    pl_stats.push_back(player_2);

                    socket.receive((char*)name3_size,sizeof(name3_size),bytes_received);
                    name3_size[0]=le32toh(name3_size[0]);
                    int name3_size_=int(name3_size[0]);
                    char name3[name3_size_];
                    socket.receive(name3, name3_size_,bytes_received);

                    socket.receive((char*)score3_final,sizeof(score3_final),bytes_received);
                    score3_final[0]=le32toh(score3_final[0]);

                    socket.receive((char*)kills3_final,sizeof(kills3_final),bytes_received);
                    kills3_final[0]=le32toh(kills3_final[0]);


                    socket.receive((char*)score3_size,sizeof(score3_size),bytes_received);
                    score3_size[0]=le32toh(score3_size[0]);


                    std::string name3__(name1);
                    std::string name3_final=name3__.substr(0,name3_size_);

                    Player_stats player_3;
                    player_3.Nickname=name3_final;
                    player_3.score=score3_size[0];
                    player_3.final_score=score3_final[0];
                    player_3.kills=kills3_final[0];
                    pl_stats.push_back(player_3);


                    socket.receive((char*)name4_size,sizeof(name4_size),bytes_received);
                    name4_size[0]=le32toh(name4_size[0]);
                    int name4_size_=int(name4_size[0]);
                    char name4[name4_size_];
                    socket.receive(name4, name4_size_,bytes_received);

                    socket.receive((char*)score4_final,sizeof(score4_final),bytes_received);
                    score4_final[0]=le32toh(score4_final[0]);

                    socket.receive((char*)kills4_final,sizeof(kills4_final),bytes_received);
                    kills4_final[0]=le32toh(kills4_final[0]);

                    socket.receive((char*)score4_size,sizeof(score4_size),bytes_received);
                    score4_size[0]=le32toh(score4_size[0]);

                    std::string name4__(name4);
                    std::string name4_final=name4__.substr(0,name4_size_);

                    Player_stats player_4;
                    player_4.Nickname=name4_final;
                    player_4.score=score4_size[0];
                    player_4.final_score=score4_final[0];
                    player_4.kills=kills4_final[0];
                    pl_stats.push_back(player_4);


                    socket.receive((char*)name5_size,sizeof(name5_size),bytes_received);
                    name5_size[0]=le32toh(name5_size[0]);
                    int name5_size_=int(name5_size[0]);
                    char name5[name5_size_];
                    socket.receive(name5, name5_size_,bytes_received);

                    socket.receive((char*)score5_final,sizeof(score5_final),bytes_received);
                    score5_final[0]=le32toh(score5_final[0]);

                    socket.receive((char*)kills5_final,sizeof(kills5_final),bytes_received);
                    kills5_final[0]=le32toh(kills5_final[0]);


                    socket.receive((char*)score5_size,sizeof(score5_size),bytes_received);
                    score5_size[0]=le32toh(score5_size[0]);


                    std::string name5__(name5);
                    std::string name5_final=name5__.substr(0,name5_size_);
                    Player_stats player_5;
                    player_5.Nickname=name5_final;
                    player_5.score=score5_size[0];
                    player_5.final_score=score5_final[0];
                    player_5.kills=kills5_final[0];
                    pl_stats.push_back(player_5);
                    
                    for(int i=0; i < int(num_players[0]); i++){
                        final_stats.push_back(pl_stats[i]);
                    }

                    update_message->load_game_stats(final_stats);
                    recv_queue.push(std::move(update_message));
                    break;
                }
                case START_EV:{
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
                    update_message->load_item_taken(player_id[0],pos_x[0],pos_y[0],value[0]);
                    recv_queue.push(std::move(update_message));
                    break;
                }
                case MACHINE_GUN_DROPPED_ITM: // pos x, pos y
                case CHAIN_CANNON_DROPPED_ITM: // pos x, pos y
                case BULLETS_DROPPED_ITM:{
                    uint32_t pos_x[1];
                    uint32_t pos_y[1];
                    
                    socket.receive((char*)pos_x, sizeof(pos_x),bytes_received);
                    socket.receive((char*)pos_y, sizeof(pos_y),bytes_received);
                    pos_x[0]=le32toh(pos_x[0]);
                    pos_y[0]=le32toh(pos_y[0]);
                    
                    update_message->load_drop(pos_x[0],pos_y[0]);
                    recv_queue.push(std::move(update_message));

                    break;
                }
                default:
                    throw Exception("Unknown item type.");
                    break;
            }
        }
    }
    catch(...){
        std::cerr << "Socket closed" << std::endl;
    }
}

void ClientSocket::send(uint8_t msg){
    uint8_t opcode=128;
    uint8_t buffer[2];
    buffer[0] = opcode;
    buffer[1] = msg;
    socket.send((char*)buffer, 2);
}
