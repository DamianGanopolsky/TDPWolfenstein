#include "command_interact.h"
#include "./../constants/const_object_map.h"

bool CommandInteract::interactWith(Player &player, int **map, BlockingObject &obj) {
    return false;
}

bool CommandInteract::interactWith(Player &player, int **map, NonBlockingObject &obj) {
    return true;
}

bool CommandInteract::interactWith(Player &player, int **map, Door &door) {
    if(!door.isOpened()) {
        door.open();
    }
    return true;
}
/*
bool CommandInteract::interactWith(Player player, int *map, LockedDoor &door) {
    if(!door.isOpened()) {
        if(! door.open()){
            return false;
        }
    }
    return true;
}*/

bool CommandInteract::interactWith(Player &player, int **map, SecretPassage &SecretPassage) {
    return true;
}

bool CommandInteract::interactWith(Player &player, int **map, Item &item) {
    PlayerInfo pi = player.getInfo();
    CommandPickUp pickuper;
    bool was_picked_up = pickuper.pickUp(pi, item);
    if (was_picked_up) {
        PlayerPosition pos = player.getPos();
        map[pos.getX()][pos.getY()] = MAP_NONE;
    }
    return was_picked_up;
}

bool CommandInteract::interactWith(Player &player, int **map, Object &object) {
    return true;
}
