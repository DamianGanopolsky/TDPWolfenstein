#include "interactor.h"
#include "./../constants/const_object_map.h"

bool Interact::interactWith(Player &player, int **map, BlockingObject &obj) {
    return false;
}

bool Interact::interactWith(Player &player, int **map, NonBlockingObject &obj) {
    return true;
}

bool Interact::interactWith(Player &player, int **map, SecretPassage &SecretPassage) {
    return true;
}

bool Interact::interactWith(Player &player, int **map, Item &item) {
    PlayerInfo pi = player.getInfo();
    PickUp pickuper;
    bool is_picked_up = pickuper.pickUp(pi, item);
    if (is_picked_up) {
        PlayerPosition pos = player.getPos();
        map[pos.getX()][pos.getY()] = MAP_NONE;
    }
    return is_picked_up;
}

bool Interact::interactWith(Player &player, int **map, Object &object) {
    return true;
}
