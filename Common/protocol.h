#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdint.h>
#include <string>

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




enum Opcode {
    EVENT_OPCODE = 0,
    ITEM_CHANGED_OPCODE,
    MESSAGE_OPCODE,
    COMMAND_OPCODE = 128
};

//Client -> Server
enum CommandOpcode {
    START_MOVING_UP_CMD = 0,    //OK
    START_MOVING_DOWN_CMD,      //OK
    START_MOVING_LEFT_CMD,     //OK
    START_MOVING_RIGHT_CMD,    //OK
    STOP_MOVING_CMD,           //OK
    START_ROTATING_LEFT,
    START_ROTATING_RIGHT,
    STOP_ROTATING,

    //USE_WEAPON_CMD, // "Boton e"  OK
    START_SHOOTING_CMD,
    STOP_SHOOTING_CMD,
    //RECIEVE_ATTACK_CMD, 
    OPEN_DOOR_CMD, //CLick derecho: posx,posy (de donde clickie)   OK
    CHANGE_WEAPON_TO_KNIFE_CMD, // Cliente selecciono el 1   OK
    CHANGE_WEAPON_TO_GUN_CMD, // Cliente selecciono el 2   OK
    CHANGE_WEAPON_TO_MACHINE_GUN_CMD, // Cliente selecciono el 3  OK
    CHANGE_WEAPON_TO_CHAIN_CANNON_CMD, // Cliente selecciono el 4  OK
}; 

//Server -> Client
enum EventOpcode {
    MOVEMENT_EV = 0,   //id del jugador, coordenada x, coordenada y, angulo del jugador, moviendo (1-si o 0-no), disparando (si o no)
    NEW_PLAYER_EV,  //id del jugador, id del mapa a abrir, coordenada x, coordenada y, angulo del jugador,vida , cant de resurrecciones 
                    //(la cant de vidas se puede obtener restando a la cte de vidas la cant de veces que resucito), puntaje, balas
    ATTACK_EV,      //id del jugador,  CANT DE BALAS
    BE_ATTACKED_EV, //id del jugador, entero con la vida que tengo( la que voy a mostrar)
    DEATH_EV,       //id del jugador, coordenada x, coordenada y //(la llegada de este evento tambien implica que se dropean los objetos a la hora de la muerte)
    RESURRECT_EV,   //id del jugador, id del mapa a abrir, coordenada x, coordenada y, angulo del jugador,vida , las vidas, puntaje, balas
    // Si el resultado de la cuenta es 0, muestro la pantalla
    //CHANGE_LEVEL_EV, // No hace falta aunque sea por ahora
    CHANGE_WEAPON_EV, //id del jugador, {0,1,2,3} 0=CUCHILLO, 1=pistola, ...
    SCORES_EV, // cant de jugadores(por si son menos de 5), nickname_1, puntos_finales_1, cant_asesinatos_1, tesoros_1,nickname_2, puntos_2,...
    START_EV //no mando nada mas que el opcode
};

enum ItemOpcode {
    CLOSE_DOOR_ITM = 0, //  pos x, pos y " posicion de la puerta"
    OPEN_DOOR_ITM, // pos x, pos y " posicion de la puerta"
    MEDICAL_KIT_TAKEN_ITM, //id del jugador que lo agarra, pos x, pos y, vida del jugador
    FOOD_TAKEN_ITM, //id del jugador que lo agarra, pos x, pos y, vida del jugador
    BLOOD_TAKEN_ITM,
    KEY_TAKEN_ITM, // id del jugador que lo agarra, pos x, pos y, keys del jugador
    WEAPON_TAKEN_ITM, // id del jugador que lo agarra, pos x, pos y
    TREASURE_TAKEN_ITM, //id del jugador que lo agarra, pos x, pos y, puntaja del jugador
    BULLETS_TAKEN_ITM, //id del jugador que lo agarra, pos x, pos y, balas del jugador
    MACHINE_GUN_DROPPED_ITM, // pos x, pos y
    CHAIN_CANNON_DROPPED_ITM, // pos x, pos y
    BULLETS_DROPPED_ITM // pos x, pos y
};

enum MessageOpcode {
    SUCCESS_MSSG = 0,
    ERROR_MSSG
};

#endif