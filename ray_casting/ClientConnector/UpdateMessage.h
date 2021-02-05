#ifndef __UPDATEMESSAGE_H__
#define __UPDATEMESSAGE_H__

#include <stdint.h>
#include "../../Common/protocol.h"

class UpdateMessage {
public:
    UpdateMessage(uint8_t opcode,uint8_t type_of_event);
    UpdateMessage(const UpdateMessage& other);
    UpdateMessage& operator=(const UpdateMessage& other);

    void load_movement_event(uint8_t player_id,uint8_t pos_x,uint8_t pos_y,\
    float angle,uint8_t is_moving,uint8_t is_shooting);

    void load_new_player_event(uint8_t player_id,uint8_t map,uint32_t pos_x,uint32_t pos_y,\
    float angle,uint32_t life,uint8_t resurrected,uint32_t score,uint32_t bullets);

    uint8_t get_opcode();

    uint8_t get_event_type();

    Movement_event get_mov_event_info();

    New_Player_Event get_new_player_info();

private:
    uint8_t Opcode;
    uint8_t Type_Of_Event;

    Movement_event MovEvent;

    New_Player_Event NewPEvent;

    /*uint8_t Player_Id;
    uint8_t Pos_X;
    uint8_t Pos_Y;
    float Angle;
    uint8_t Is_Moving;
    uint8_t Is_Shooting;*/

};

#endif