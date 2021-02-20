#ifndef __UPDATEMESSAGE_H__
#define __UPDATEMESSAGE_H__

#include <vector>
#include <string>
#include <stdint.h>
#include "../../Common/protocol.h"
#include "../const.h"

class UpdateMessage {
public:
    UpdateMessage(uint8_t opcode,uint8_t type_of_event);
    UpdateMessage(const UpdateMessage& other);
    UpdateMessage& operator=(const UpdateMessage& other);

    void load_movement_event(uint32_t player_id,uint32_t pos_x,uint32_t pos_y,\
    float angle,uint8_t is_moving,uint8_t is_shooting);

    void load_new_player_event(uint8_t player_id,uint32_t pos_x,uint32_t pos_y,\
    float angle,uint32_t life,uint8_t resurrected,uint32_t score,uint32_t bullets);

    void load_death_event(uint32_t player_id,uint32_t pos_x,uint32_t pos_y);

    void load_changed_stat(uint32_t player_id,uint32_t weapon);

    void load_door_changed(uint32_t x,uint32_t y);

    void load_item_taken(uint32_t player_id,uint32_t pos_x,uint32_t pos_y,uint32_t value);

    void load_game_stats(std::vector<Player_stats> final_stats);

    uint8_t get_opcode();

    uint8_t get_event_type();

    Movement_event get_mov_event_info();

    New_Player_Event get_new_player_info();

    Change_Weapon_Event get_changed_stat();

    Change_door_event get_changed_door();

    Item_taken_event get_item_taken();

    Death_event get_death_event();

    std::vector<Player_stats> get_final_stats();

private:
    uint8_t Opcode;
    uint8_t Type_Of_Event;

    Movement_event MovEvent;

    New_Player_Event NewPEvent;

    Change_Weapon_Event ChWeaponEvent;

    Change_door_event ChDoorEvent;

    Item_taken_event ItTakenEvent;

    Death_event death_event;

    std::vector<Player_stats> final_stats;

    /*uint8_t Player_Id;
    uint8_t Pos_X;
    uint8_t Pos_Y;
    float Angle;
    uint8_t Is_Moving;
    uint8_t Is_Shooting;*/

};

#endif