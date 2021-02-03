#ifndef __UPDATEMESSAGE_H__
#define __UPDATEMESSAGE_H__

#include <stdint.h>

class UpdateMessage {
public:
    UpdateMessage(uint8_t opcode,uint8_t type_of_event);
    UpdateMessage(const UpdateMessage& other);
    UpdateMessage& operator=(const UpdateMessage& other);

    void load_movement_event(uint8_t player_id,uint8_t pos_x,uint8_t pos_y,\
    float angle,uint8_t is_moving,uint8_t is_shooting);

private:
    uint8_t Opcode;
    uint8_t Type_Of_Event;

    uint8_t Player_Id;
    uint8_t Pos_X;
    uint8_t Pos_Y;
    float Angle;
    uint8_t Is_Moving;
    uint8_t Is_Shooting;

};

#endif