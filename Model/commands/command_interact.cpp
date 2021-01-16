#include "command_interact.h"
#include "./../constants/const_object_map.h"

bool CommandInteract::interactWith(Player &player, int **map, BlockingObject &obj) {
    return false;
}

bool CommandInteract::interactWith(Player &player, int **map, NonBlockingObject &obj) {
    return true;
}

bool CommandInteract::interactWith(Player &player, int **map, SecretPassage &SecretPassage) {
    return true;
}

bool CommandInteract::interactWith(Player &player, int **map, Item &item) {
    PlayerInfo pi = player.getInfo();
    CommandPickUp pickuper;
    bool is_picked_up = pickuper.pickUp(pi, item);
    if (is_picked_up) {
        PlayerPosition pos = player.getPos();
        map[pos.getX()][pos.getY()] = MAP_NONE;
    }
    return is_picked_up;
}

/*bool CommandInteract::interactWith(Player &player, int **map, Item &item, bool drop) {
    if (drop) {
        PlayerInfo pi = player.getInfo();
        CommandDrop droper;
        int is_dropped = droper.drop(pi, item);
        if (is_dropped) {
            PlayerPosition pos = player.getPos();
            map[pos.getX()][pos.getY()] = is_dropped;
        }
        return is_dropped;
    }
    return false;
}*/

bool CommandInteract::interactWith(Player &player, int **map, Object &object) {
    return true;
}
