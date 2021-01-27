// ATENCION: config temporal (después pasar a formato YAML)

#ifndef CONFIG_PLAYER_H
#define CONFIG_PLAYER_H

// Player
#define MAX_RESURRECTIONS 2
#define ROTATION_SIZE 3.0
#define DISPLACEMENT 5
#define PI 3.14159265

#define SUCCESS_MSG "Success."
#define PLAYER_DIED_MSG "Success: Player died."
#define CANT_ATTACK_ITSELF_ERROR_MSG "ERROR: Player can't attack itself."
#define CANT_BE_ATTACKED_ERROR_MSG "ERROR: Player can't attack other player."
#define STATE_CANT_ATTACK_ERROR_MSG "ERROR: Player has a state that doesn't allow him to attack."
#define STATE_CANT_RESURRECT_ERROR_MSG "ERROR: Player has a state that doesn't allow him to resurrect."
#define MAX_RESURRECTIONS_REACHED_ERROR_MSG "ERROR: Player has already resurrected as many times as possible."
#define NO_KEY_TO_OPEN_CLOSED_DOOR "ERROR: Player hasn't a key to open this locked door."
#define CANT_MOVE_UP_ERROR_MSG "ERROR: Player can't move up."
#define CANT_MOVE_DOWN_ERROR_MSG "ERROR: Player can't move down."
#define CANT_MOVE_RIGHT_ERROR_MSG "ERROR: Player can't move right."
#define CANT_MOVE_LEFT_ERROR_MSG "ERROR: Player can't move left."
#define NO_WEAPON_IN_INVENTORY_ERROR_MSG "ERROR: Weapon not found in inventory."
#endif