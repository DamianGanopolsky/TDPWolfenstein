 #include "ReceiveController.h"




 void ReceiveController::ExecuteEvent(){
     //player.move_right();
 }
/*
 void ReceiveController::InitializeClient(New_Player_Event& my_player){
     std::cout << "El id de mi  player es" << my_player.player_id << std::endl;
     player(my_player.pos_x,my_player.pos_y,my_player.angle);
 }
*/


bool ReceiveController::start(){
     //POP
     UpdateMessage* updatemessage=recv_queue.pop();
     if(!updatemessage){
         //std::cout << "No se popeo nada" << std::endl;
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
                        if(mov_event.is_shooting==1){
                            player.shoot();
                        }
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
                        map.update_player_pos(new_ev.player_id,\
                        new_ev.pos_x,new_ev.pos_y,new_ev.angle,0);
                    }
                    //std::cout << "lives es" << unsigned(new_ev.life) << std::endl;
                    break;
                }
                case CHANGE_WEAPON_EV:{
                    Change_Weapon_Event weapon_ev=updatemessage->get_changed_stat();
                    //Chequear si el casteo esta bien
                    if(int(weapon_ev.player_id)!=player.get_id()){
                        map.update_player_texture(weapon_ev.player_id,weapon_ev.weapon);
                    }
                    else{
                        player.change_weapon(weapon_ev.player_id);
                    }
                    break;
                }
                case ATTACK_EV:{
                    Change_Weapon_Event attack_ev=updatemessage->get_changed_stat();
                    if(int(attack_ev.player_id)==player.get_id()){
                        player.shoot();
                    }
                    break;
                }
                default:
                    break;
             }
         }
         if(updatemessage->get_opcode()==1){
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
                    map.delete_item(it_taken.pos_x,it_taken.pos_y);
                    if(int(it_taken.player_id)==player.get_id()){
                        player.add_bullets(it_taken.value);
                    }
                }
             }
         }
     }
     return false;
     
     //DIBUJAR
 }