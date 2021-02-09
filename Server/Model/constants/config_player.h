// ATENCION: config temporal (después pasar a formato YAML)

#ifndef CONFIG_PLAYER_H
#define CONFIG_PLAYER_H

// Player
#define MAX_RESURRECTIONS 2
#define ROTATION_SIZE 3.0
#define DISPLACEMENT 5
#define PI 3.14159265

//player position direction
enum Direction {
    UP_DIR = 0,
    DOWN_DIR,
    LEFT_DIR,
    RIGHT_DIR,
};
//player position rotation
enum Rotation {
    LEFT_ROTATION_DIR = 0,
    RIGHT_ROTATION_DIR
};

enum ItemPickedUp {
    NO_ITEM_PICKED_UP = 0,
    BULLETS_PICKED_UP,
    FOOD_PICKED_UP,
    KIT_PICKED_UP,
    BLOOD_PICKED_UP,
    KEY_PICKED_UP,
    TREASURE_PICKED_UP,
    WEAPON_PICKED_UP
};

#define SUCCESS_MSG "Success."
//picked up items success
#define ITEM_PICKED_UP_MSG "Success: Item picked up."
#define NO_ITEM_PICKED_UP_MSG "Success: No item picked up."
/*
#define BULLETS_PICKED_UP_MSG "Success: Bullets picked up."
#define FOOD_PICKED_UP_MSG "Success: Food picked up."
#define KIT_PICKED_UP_MSG "Success: Kit picked up."
#define BLOOD_PICKED_UP_MSG "Success: Blood picked up."
#define KEY_PICKED_UP_MSG "Success: Key picked up."
#define TREASURE_PICKED_UP_MSG "Success: Treasure picked up."
#define WEAPON_PICKED_UP_MSG "Success: Weapon picked up."
*/
//player death succes
#define PLAYER_DIED_MSG "Success: Player died."
#define CANT_ATTACK_ITSELF_ERROR_MSG "ERROR: Player can't attack itself."
#define CANT_ATTACK_UNKNOWN_ID_ERROR_MSG "ERROR: Player can't attack an unknown player id."
#define CANT_ATTACK_WITHOUT_BULLETS_ERROR_MSG "ERROR: Player can't attack without bullets."
#define CANT_BE_ATTACKED_ERROR_MSG "ERROR: Player can't attack other player."
#define STATE_CANT_ATTACK_ERROR_MSG "ERROR: Player has a state that doesn't allow him to attack."
#define STATE_CANT_RESURRECT_ERROR_MSG "ERROR: Player has a state that doesn't allow him to resurrect."
#define MAX_RESURRECTIONS_REACHED_ERROR_MSG "ERROR: Player has already resurrected as many times as possible."
#define NO_KEY_TO_OPEN_CLOSED_DOOR "ERROR: Player hasn't a key to open this locked door."
#define CANT_MOVE_ERROR_MSG "ERROR: Player can't move."
#define CANT_MOVE_UP_ERROR_MSG "ERROR: Player can't move up."
#define CANT_MOVE_DOWN_ERROR_MSG "ERROR: Player can't move down."
#define CANT_MOVE_RIGHT_ERROR_MSG "ERROR: Player can't move right."
#define CANT_MOVE_LEFT_ERROR_MSG "ERROR: Player can't move left."
#define NO_WEAPON_IN_INVENTORY_ERROR_MSG "ERROR: Weapon not found in inventory."

#endif