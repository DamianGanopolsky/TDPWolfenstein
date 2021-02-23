#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdint.h>
#include <string>

enum Opcode {
    EVENT_OPCODE = 0,
    ITEM_CHANGED_OPCODE,
    COMMAND_OPCODE
};

//Client -> Server
enum CommandOpcode {
    START_MOVING_UP_CMD = 0,    
    START_MOVING_DOWN_CMD,
    START_MOVING_LEFT_CMD,
    START_MOVING_RIGHT_CMD,
    STOP_MOVING_CMD, 
    START_ROTATING_LEFT,
    START_ROTATING_RIGHT,
    STOP_ROTATING,
    START_SHOOTING_CMD,
    STOP_SHOOTING_CMD, 
    OPEN_DOOR_CMD, 
    CHANGE_WEAPON_TO_KNIFE_CMD, 
    CHANGE_WEAPON_TO_GUN_CMD, 
    CHANGE_WEAPON_TO_MACHINE_GUN_CMD,
    CHANGE_WEAPON_TO_CHAIN_CANNON_CMD
}; 

//Server -> Client
enum EventOpcode {
    MOVEMENT_EV = 0,   
    NEW_PLAYER_EV,
    ATTACK_EV, 
    BE_ATTACKED_EV,
    DEATH_EV,
    RESURRECT_EV,
    CHANGE_WEAPON_EV,
    SCORES_EV,
    START_EV
};

enum ItemOpcode {
    CLOSE_DOOR_ITM = 0, 
    OPEN_DOOR_ITM,
    MEDICAL_KIT_TAKEN_ITM,
    FOOD_TAKEN_ITM,
    BLOOD_TAKEN_ITM,
    KEY_TAKEN_ITM,
    WEAPON_TAKEN_ITM,
    TREASURE_TAKEN_ITM,
    BULLETS_TAKEN_ITM,
    MACHINE_GUN_DROPPED_ITM,
    CHAIN_CANNON_DROPPED_ITM, 
    BULLETS_DROPPED_ITM
};

/* Estos structs le corresponden al cliente, no deberian estar en protocol.h */
struct Movement_event {
    uint8_t player_id;
    uint32_t pos_x;
    uint32_t pos_y;
    float angle;
    uint8_t is_moving;
    uint8_t is_shooting;
};

struct New_Player_Event{
    uint32_t player_id;
    uint32_t map_len;
    std::string map;
    uint32_t pos_x;
    uint32_t pos_y;
    float angle;
    uint32_t life;
    uint8_t resurrected;
    uint32_t score;
    uint32_t bullets;
};

struct Change_Weapon_Event{
    uint32_t player_id;
    uint32_t weapon;
};

struct Change_door_event{
    uint32_t pos_x;
    uint32_t pos_y;
};

struct Item_taken_event{
    uint32_t pos_x;
    uint32_t pos_y;
    uint32_t value;
    uint32_t player_id;
};

struct Death_event{
    uint32_t id_player;
    uint32_t pos_x;
    uint32_t pos_y;
};

struct Item_dropped_event{
    uint32_t pos_x;
    uint32_t pos_y;
};

#endif