#include "command_open_door.h"
#include "./../constants/const_object_map.h"

Response CommandOpenDoor::run(Player &player, int **map) {
    PlayerPosition pos = player.getPos();

    int object_code = map[pos.getX()][pos.getY()];
    Object obj = objMap.getObject(object_code);

    bool door_opened = _interactWith(player, map, obj);
    if (!door_opened) {
        return Response(false, NO_KEY_TO_OPEN_CLOSED_DOOR);
    }
    return Response(true, SUCCESS_MSG);
}

bool CommandOpenDoor::_interactWith(Player &player, int **map, Door &door) {
    if (!door.isOpened()) {
        door.open();
    }
    return true;
}

bool CommandOpenDoor::_interactWith(Player &player, int **map, LockedDoor &door) {
    if (!door.isOpened()) {
        if (player.getInfo().getKey() != 0) {
            player.getInfo().reduceNumKeys(1);
            door.open();
            return true;
        } else {
            return false;
        }
    }
    return true;
}
