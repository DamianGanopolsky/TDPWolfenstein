 #include "ReceiveController.h"
 #include "yaml-cpp/yaml.h"

ReceiveController::ReceiveController(Player& Player,Map_2d& MAP,NonBlockingQueue<UpdateMessage*>& RECV_QUEUE,\
     Client& CLIENT):player(Player),map(MAP),recv_queue(RECV_QUEUE),client(CLIENT){
    YAML::Node data_config=YAML::LoadFile("../Yaml_configs/server_config.yaml");
    lives=data_config["max_resurrections"].as<int>();;
    std::cout << "Max resurrections es" << lives << std::endl;
}


void ReceiveController::update(){
     //POP
     UpdateMessage* updatemessage=recv_queue.pop();
     //client.render();
     if(!updatemessage){
         //Aca dibujo lo actualizado
         client.render();
     }
     
     
     //UPDATe
     else{
         if(updatemessage->get_opcode()==0){
             switch(updatemessage->get_event_type()){
                case MOVEMENT_EV:  {//MOVEMENT EVENT
                    Movement_event mov_event=updatemessage->get_mov_event_info();
                    if(mov_event.player_id==player.get_id()){   // 1 SERIA YO
                        player.update_position_and_angle(mov_event.pos_x,\
                        mov_event.pos_y,mov_event.angle);
                       /* if(mov_event.is_shooting==1){
                            player.shoot();
                        }*/
                    }
                    else{
                        map.update_player_pos(mov_event.player_id,mov_event.pos_x\
                        ,mov_event.pos_y,mov_event.angle,mov_event.is_shooting);
                    }
                    break;
                }
                case NEW_PLAYER_EV:{
                    New_Player_Event new_ev=updatemessage->get_new_player_info();
                    
                    if(int(new_ev.player_id)!=player.get_id()){
                        map.new_player(new_ev.player_id,\
                        new_ev.pos_x,new_ev.pos_y,new_ev.angle,0);
                    }
                    break;
                }
                case RESURRECT_EV:{
                   New_Player_Event resurrect_ev=updatemessage->get_new_player_info();
                   if(int(resurrect_ev.player_id)!=player.get_id()){
                       std::cout << "La id del jugador muerto es" << resurrect_ev.player_id << std::endl;
                        map.new_player(resurrect_ev.player_id,\
                        resurrect_ev.pos_x,resurrect_ev.pos_y,resurrect_ev.angle,0);
                    }
                   else{
                        std::cout << "Resurreccione y mi nueva pos es x:" << resurrect_ev.pos_x << "y:" << resurrect_ev.pos_y << std::endl;
                        /*player.update_position_and_angle(resurrect_ev.pos_x,resurrect_ev.pos_y,\
                        resurrect_ev.angle);*/
                        player.resurrect_player(resurrect_ev);
                    }
                   break;
                }
                case CHANGE_WEAPON_EV:{
                    Change_Weapon_Event weapon_ev=updatemessage->get_changed_stat();
                    if(int(weapon_ev.player_id)!=player.get_id()){
                        map.update_player_texture(weapon_ev.player_id,weapon_ev.weapon-1);
                    }
                    else{
                        player.change_weapon(weapon_ev.weapon-1);
                    }
                    break;
                }
                case ATTACK_EV:{
                    Change_Weapon_Event attack_ev=updatemessage->get_changed_stat();
                    std::cout << "Player id:" << attack_ev.player_id <<"Bullets:" << attack_ev.weapon << std::endl;
                    if(int(attack_ev.player_id)==player.get_id()){
                        player.shoot(attack_ev.weapon);
                    }
                    else{
                        if(map.get_player_weapon(attack_ev.player_id)!=0){
                            soundmanager.play_sound(map.get_player_weapon(attack_ev.player_id));
                        }
                        map.player_shoot(attack_ev.player_id);
                    }
                    break;
                }
                case DEATH_EV:{
                    Death_event death_ev=updatemessage->get_death_event();
                    if(int(death_ev.id_player)==player.get_id()){
                        lives=lives-1;
                        if(lives==-1){
                            client.player_lost();
                            std::cout << "Me quede sin vidas" << std::endl;
                        }
                    }
                    else{
                        soundmanager.play_sound(DEATH);
                    }
                    map.add_dead_body(death_ev.id_player,death_ev.pos_x,death_ev.pos_y);
                    break;
                }
                case BE_ATTACKED_EV:{
                    Change_Weapon_Event attack_ev=updatemessage->get_changed_stat();
                    if(int(attack_ev.player_id)==player.get_id()){
                        player.change_health(attack_ev.weapon);
                    }
                    break;
                }
                default:
                    break;
             }
         }
         if(updatemessage->get_opcode()==ITEM_CHANGED_OPCODE){
             //std::cout << "CHANGE ITEM EVENT" << std::endl;
             switch(updatemessage->get_event_type()){
                case CLOSE_DOOR_ITM:{
                    Change_door_event change_door=updatemessage->get_changed_door();
                    map.close_door(change_door.pos_x,change_door.pos_y);
                    break;
                }
                case OPEN_DOOR_ITM:{
                    Change_door_event change_door=updatemessage->get_changed_door();
                    map.open_door(change_door.pos_x,change_door.pos_y);
                    break;
                }
                case BULLETS_TAKEN_ITM:{
                    Item_taken_event it_taken=updatemessage->get_item_taken();
                    //std::cout << "Pos x es :" << it_taken.pos_x << "Pos y es: " << it_taken.pos_y << std::endl;
                    map.delete_item(it_taken.pos_x,it_taken.pos_y);
                    if(int(it_taken.player_id)==player.get_id()){
                        player.add_bullets(it_taken.value);
                    }
                    break;
                }
                case MEDICAL_KIT_TAKEN_ITM:{
                    Item_taken_event it_taken=updatemessage->get_item_taken();
                    map.delete_item(it_taken.pos_x,it_taken.pos_y);
                    if(int(it_taken.player_id)==player.get_id()){
                        player.change_health(it_taken.value);
                    }
                    break;
                }
                case FOOD_TAKEN_ITM:{
                    Item_taken_event it_taken=updatemessage->get_item_taken();
                    map.delete_item(it_taken.pos_x,it_taken.pos_y);
                    if(int(it_taken.player_id)==player.get_id()){
                        player.change_health(it_taken.value);
                    }
                    break;
                }
                case WEAPON_TAKEN_ITM:{
                    Item_taken_event it_taken=updatemessage->get_item_taken();
                    map.delete_item(it_taken.pos_x,it_taken.pos_y);
                    if(int(it_taken.player_id)==player.get_id()){
                        soundmanager.play_sound(EQUIP_WEAPON);
                    }
                    break;
                }
                case TREASURE_TAKEN_ITM:{
                    std::cout << "Recibi tesoro" << std::endl;
                    //client.player_lost();
                    
                    Item_taken_event it_taken=updatemessage->get_item_taken();
                    
                    std::cout << "Cuadricula x es" << it_taken.pos_x << "Cuadricula y es" << it_taken.pos_y << std::endl;
                    map.delete_item(it_taken.pos_x,it_taken.pos_y);
                    if(int(it_taken.player_id)==player.get_id()){
                        player.change_score(it_taken.value);
                    }
                    break;
                }
             }
         }
         //client.render();
     }  
 }