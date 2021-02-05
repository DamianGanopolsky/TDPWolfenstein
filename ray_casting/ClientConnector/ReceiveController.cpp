 #include "ReceiveController.h"




 void ReceiveController::ExecuteEvent(){
     //player.move_right();
 }



bool ReceiveController::start(){
     //POP
     UpdateMessage* updatemessage=recv_queue.pop();
     if(!updatemessage){
         //std::cout << "No se popeo nada" << std::endl;
         client.render();
     }
     
     else{
         if(updatemessage->get_opcode()==0){
             switch(updatemessage->get_event_type()){
                case 0:  {//MOVEMENT EVENT
                    Movement_event mov_event=updatemessage->get_mov_event_info();
                    if(mov_event.player_id==1){   // 1 SERIA YO
                        player.update_position_and_angle(mov_event.pos_x,\
                        mov_event.pos_y,mov_event.angle);
                    }
                    else{
                        map.update_player_pos(mov_event.player_id,\
                        mov_event.pos_x,mov_event.pos_y,mov_event.angle);
                    }
                    break;
                }
                case NEW_PLAYER_EV:{
                    New_Player_Event new_ev=updatemessage->get_new_player_info();
                    /*if(new_ev.life==1){
                        player.get_info.
                    }*/
                    std::cout << "lives es" << unsigned(new_ev.life) << std::endl;
                    break;
                }
                default:
                    break;

             }
         }
     }


     return false;
     //UPDATE
     //DIBUJAR
 }