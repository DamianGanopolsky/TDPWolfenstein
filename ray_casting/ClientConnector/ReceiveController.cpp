 #include "ReceiveController.h"




 void ReceiveController::ExecuteEvent(){
     //player.move_right();
 }

 void ReceiveController::InitializeClient(New_Player_Event& my_player){
     std::cout << "El id de mi  player es" << my_player.player_id << std::endl;
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
                case MOVEMENT_EV:  {//MOVEMENT EVENT
                    Movement_event mov_event=updatemessage->get_mov_event_info();
                    if(mov_event.player_id==1){   // 1 SERIA YO
                        player.update_position_and_angle(mov_event.pos_x,\
                        mov_event.pos_y,mov_event.angle);
                    }
                    else{
                        
                    }
                    break;
                }
                case NEW_PLAYER_EV:{
                    New_Player_Event new_ev=updatemessage->get_new_player_info();
                    
                    if(new_ev.player_id==1){
                        player.get_info().set_initial_status(new_ev.life,new_ev.resurrected,\
                    new_ev.score,new_ev.bullets);
                    }
                    else{
                        map.update_player_pos(new_ev.player_id,\
                        new_ev.pos_x,new_ev.pos_y,new_ev.angle);
                    }
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