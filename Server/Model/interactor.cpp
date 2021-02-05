#include "interactor.h"
#include "./constants/const_object_map.h"

Interact::Interact() {}

Interact::~Interact() {}

Response Interact::interactWith(Player &player, Map& map, BlockingObject &obj) {
    return Response(false, NO_ITEM_PICKED_UP_MSG);
}

Response Interact::interactWith(Player &player, Map& map, NonBlockingObject &obj) {
    return Response(true, NO_ITEM_PICKED_UP_MSG);
}

Response Interact::interactWith(Player &player, Map& map, SecretPassage &SecretPassage) {
    return Response(true, NO_ITEM_PICKED_UP_MSG);
}

Response Interact::interactWith(Player &player, Map& map, Item &item) {
    PlayerInfo pi = player.getInfo();
    PickUp pickuper;
    Response is_picked_up = pickuper.pickUp(pi, item);
    if (is_picked_up.success) {
        PlayerPosition pos = player.getPos();
        map.setObjectPos(pos.getX(), pos.getY(), MAP_NONE);
        Response(true, is_picked_up.message);
    }
    return Response(true, NO_ITEM_PICKED_UP_MSG);
}

Response Interact::interactWith(Player &player, Map& map, Object &object) {
    return Response(true, NO_ITEM_PICKED_UP_MSG);
}