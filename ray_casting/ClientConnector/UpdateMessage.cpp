#include "UpdateMessage.h"


UpdateMessage::UpdateMessage(uint8_t opcode,uint8_t type_of_event):\
    Opcode(opcode),Type_Of_Event(type_of_event){

}

void UpdateMessage::load_movement_event(uint8_t player_id,uint8_t pos_x,uint8_t pos_y,\
    float angle,uint8_t is_moving,uint8_t is_shooting){
    Player_Id=player_id;
    Pos_X=pos_x;
    Pos_Y=pos_y;
    Angle=angle;
    Is_Moving=is_moving;
    Is_Shooting=is_shooting;
}