#include "UpdateMessage.h"


UpdateMessage::UpdateMessage(const UpdateMessage& other) {
    this->Opcode = other.Opcode;
    this->Type_Of_Event=other.Type_Of_Event;
    this->MovEvent=other.MovEvent;
    this->NewPEvent=other.NewPEvent;
    this->ChWeaponEvent=other.ChWeaponEvent;
    this->ChDoorEvent=other.ChDoorEvent;
    this->ItTakenEvent=other.ItTakenEvent;
    this->death_event=other.death_event;
}
UpdateMessage& UpdateMessage::operator=(const UpdateMessage& other) {
    this->Opcode = other.Opcode;
    this->Type_Of_Event=other.Type_Of_Event;
    this->MovEvent=other.MovEvent;
    this->NewPEvent=other.NewPEvent;
    this->ChWeaponEvent=other.ChWeaponEvent;
    this->ChDoorEvent=other.ChDoorEvent;
    this->ItTakenEvent=other.ItTakenEvent;
    this->death_event=other.death_event;
    return *this;
}


UpdateMessage::UpdateMessage(uint8_t opcode,uint8_t type_of_event):\
    Opcode(opcode),Type_Of_Event(type_of_event){

}

void UpdateMessage::load_changed_stat(uint32_t player_id,uint32_t weapon){
    ChWeaponEvent.player_id=player_id;
    ChWeaponEvent.weapon=weapon;
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

void UpdateMessage::load_new_player_event(uint8_t player_id,uint32_t pos_x,uint32_t pos_y,\
    float angle,uint32_t life,uint8_t resurrected,uint32_t score,uint32_t bullets){
        NewPEvent.player_id=player_id;
       // NewPEvent.map=map;
        NewPEvent.pos_x=pos_x;
        NewPEvent.pos_y=pos_y;
        NewPEvent.angle=angle;
        NewPEvent.life=life;
        NewPEvent.resurrected=resurrected;
        NewPEvent.score=score;
        NewPEvent.bullets=bullets;
}

void UpdateMessage::load_door_changed(uint32_t pos_x,uint32_t pos_y){
    ChDoorEvent.pos_x=pos_x;
    ChDoorEvent.pos_y=pos_y;
}

void UpdateMessage::load_item_taken(uint32_t player_id,uint32_t pos_x,uint32_t pos_y,uint32_t value){
    ItTakenEvent.player_id=player_id;
    ItTakenEvent.pos_x=pos_x;
    ItTakenEvent.pos_y=pos_y;
    ItTakenEvent.value=value;

}

void UpdateMessage::load_death_event(uint32_t player_id,uint32_t pos_x,uint32_t pos_y){
    death_event.id_player=player_id;
    death_event.pos_x=pos_x;
    death_event.pos_y=pos_y;
}



Movement_event UpdateMessage::get_mov_event_info(){
    return MovEvent;
}

New_Player_Event UpdateMessage::get_new_player_info(){
    return NewPEvent;
}

Change_Weapon_Event UpdateMessage::get_changed_stat(){
    return ChWeaponEvent;
}

Change_door_event UpdateMessage::get_changed_door(){
    return ChDoorEvent;
}

Item_taken_event UpdateMessage::get_item_taken(){
    return ItTakenEvent;
}

Death_event UpdateMessage::get_death_event(){
    return death_event;
}


uint8_t UpdateMessage::get_opcode(){
    return Opcode;
}

uint8_t UpdateMessage::get_event_type(){
    return Type_Of_Event;
}