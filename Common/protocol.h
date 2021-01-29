#ifndef PROTOCOL_H
#define PROTOCOL_H

enum Opcode {
    EVENT_OPCODE = 0,
    ITEM_CHANGED_OPCODE,
    MESSAGE_OPCODE,
    COMMAND_OPCODE = 128
};
//LO QUe el cliente le manda al servidor
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
//Lo que el servidor le manda al cliente
enum EventOpcode {
    NEW_PLAYER_EV,  //Coordenada x, coordenada y, angulo del jugador, id del jugador(que jugador),
                    //vida , las vidas, puntaje, balas, id del mapa a abrir
    MOVEMENT_EV = 0, //Coordenada x, coordenada y, angulo del jugador, id del jugador(que jugador)
                    // moviendo (si o no), disparando (si o no)
                     
    ATTACK_EV,      //Si puedo o si no puedo disparar
    BE_ATTACKED_EV, // Entero con la vida que tengo( la que voy a mostrar)
    DEATH_EV,       //Coordenada x, coordenada y, id del jugador(que jugador)
    RESURRECT_EV,   //Coordenada x, coordenada y, angulo del jugador, id del jugador(que jugador),
                    //vida,las vidas, balas, puntaje, 
    CHANGE_LEVEL_EV, // No hace falta aunque sea por ahora
    CHANGE_WEAPON //{0,1,2,3} 0=CUCHILLO, 1=pistola, ... 
};
//Lo que el servidor le manda al cliente
enum ItemOpcode {
    //CLOSE_DOOR_ITM = 0
    MEDICAL_KIT= //id del jugador que lo agarra, pos x, pos y, vida del jugador
    FOOD //id del jugador que lo agarra, pos x, pos y, vida del jugador
    KEY // id del jugador que lo agarra, pos x, pos y, keys del jugador
    ARMAS // id del jugador que lo agarra, pos x, pos y
    TESOROS //id del jugador que lo agarra, pos x, pos y, puntaja del jugador
    BALAS //id del jugador que lo agarra, pos x, pos y, balas del jugador
    CLOSE_DOOR_ITM //  pos x, pos y " posicion de la puerta"
    OPEN_DOOR_ITEM // pos x, pos y " posicion de la puerta"

};

enum MessageOpcode {
    SUCCESS_MSSG = 0,
    ERROR_MSSG
};

#endif