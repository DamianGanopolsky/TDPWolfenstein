#include "UpdateMessage.h"


UpdateMessage::UpdateMessage(const UpdateMessage& other) {
    this->Opcode = other.Opcode;
    this->Type_Of_Event=other.Type_Of_Event;
    this->MovEvent=other.MovEvent;
    this->NewPEvent=other.NewPEvent;
}
UpdateMessage& UpdateMessage::operator=(const UpdateMessage& other) {
    this->Opcode = other.Opcode;
    this->Type_Of_Event=other.Type_Of_Event;
    this->MovEvent=other.MovEvent;
    this->NewPEvent=other.NewPEvent;
    return *this;
}


UpdateMessage::UpdateMessage(uint8_t opcode,uint8_t type_of_event):\
    Opcode(opcode),Type_Of_Event(type_of_event){

}

void UpdateMessage::load_movement_event(uint32_t player_id,uint32_t pos_x,uint32_t pos_y,\
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
        NewPEvent.player_id=player_id;
        NewPEvent.map=map;
        NewPEvent.pos_x=pos_x;
        NewPEvent.pos_y=pos_y;
        NewPEvent.angle=angle;
        NewPEvent.life=life;
        NewPEvent.resurrected=resurrected;
        NewPEvent.score=score;
        NewPEvent.bullets=bullets;

}
Movement_event UpdateMessage::get_mov_event_info(){
    return MovEvent;
}

New_Player_Event UpdateMessage::get_new_player_info(){
    return NewPEvent;
}


uint8_t UpdateMessage::get_opcode(){
    return Opcode;
}

uint8_t UpdateMessage::get_event_type(){
    return Type_Of_Event;
}