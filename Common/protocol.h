#ifndef PROTOCOL_H
#define PROTOCOL_H

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

    USE_WEAPON_CMD, // "Boton e"  OK
    //RECIEVE_ATTACK_CMD, 
    OPEN_DOOR_CMD, //CLick derecho: posx,posy (de donde clickie)   OK
    CHANGE_WEAPON_TO_KNIFE_CMD, // Cliente selecciono el 1   OK
    CHANGE_WEAPON_TO_GUN_CMD, // Cliente selecciono el 2   OK
    CHANGE_WEAPON_TO_MACHINE_GUN_CMD, // Cliente selecciono el 3  OK
    CHANGE_WEAPON_TO_CHAIN_CANNON_CMD, // Cliente selecciono el 4  OK
}; 

//Server -> Client
enum EventOpcode {
    MOVEMENT_EV,   //id del jugador, coordenada x, coordenada y, angulo del jugador, moviendo (1-si o 0-no), disparando (si o no)
    NEW_PLAYER_EV,  //id del jugador, id del mapa a abrir, coordenada x, coordenada y, angulo del jugador,vida , cant de resurrecciones 
                    //(la cant de vidas se puede obtener restando a la cte de vidas la cant de veces que resucito), puntaje, balas
    DELETE_PLAYER_EV, //id del jugador
    ATTACK_EV,      //id del jugador, disparando (si o no)
    BE_ATTACKED_EV, //id del jugador, entero con la vida que tengo( la que voy a mostrar)
    DEATH_EV,       //id del jugador, coordenada x, coordenada y (la llegada de este evento tambien implica que se dropean los objetos a la hora de la muerte)
    RESURRECT_EV,   //id del jugador, id del mapa a abrir, coordenada x, coordenada y, angulo del jugador,vida , las vidas, puntaje, balas
    //CHANGE_LEVEL_EV, // No hace falta aunque sea por ahora
    CHANGE_WEAPON_EV //id del jugador, {0,1,2,3} 0=CUCHILLO, 1=pistola, ...
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

};

enum MessageOpcode {
    SUCCESS_MSSG = 0,
    ERROR_MSSG
};

#endif