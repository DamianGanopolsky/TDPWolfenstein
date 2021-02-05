#include "UpdateMessage.h"


UpdateMessage::UpdateMessage(uint8_t opcode,uint8_t type_of_event):\
    Opcode(opcode),Type_Of_Event(type_of_event){

}

void UpdateMessage::load_movement_event(uint8_t player_id,uint8_t pos_x,uint8_t pos_y,\
    float angle,uint8_t is_moving,uint8_t is_shooting){
    MovEvent.player_id=player_id;
    MovEvent.pos_x=pos_x;
    MovEvent.pos_y=pos_y;
    MovEvent.angle=angle;
    MovEvent.is_moving=is_moving;
    MovEvent.is_shooting=is_shooting;
}

void UpdateMessage::load_new_player_event(uint8_t player_id,uint8_t map,uint32_t pos_x,uint32_t pos_y,\
    float angle,uint32_t life,uint8_t resurrected,uint32_t score,uint32_t bullets){
        NewEvent.player_id=player_id;
        NewEvent.map=map;
        NewEvent.pos_x=pos_x;
        NewEvent.pos_y=pos_y;
        NewEvent.angle=angle;
        NewEvent.life=life;
        NewEvent.resurrected=resurrected;
        NewEvent.score=score;
        NewEvent.bullets=bullets;

}
Movement_event UpdateMessage::get_event_info(){
    return MovEvent;
}


uint8_t UpdateMessage::get_opcode(){
    return Opcode;
}

uint8_t UpdateMessage::get_event_type(){
    return Type_Of_Event;
}