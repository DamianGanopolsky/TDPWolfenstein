#include "interactor.h"
#include "./constants/const_object_map.h"

Interact::Interact() {}

Interact::~Interact() {}

Response Interact::interactWith(Player &player, Map& map, Object* object) {
    if (object->isBlocking()) {
        return Response(false, NO_ITEM_PICKED_UP_MSG);
    } else if (object->isItem()) {
        PickUp pickuper;
        int is_picked_up = pickuper.pickUp(player, object->getItem());
        if (is_picked_up != NO_ITEM_PICKED_UP) {
            PlayerPosition pos = player.getPos();
            map.setObjectPos(pos.getX(), pos.getY(), MAP_NONE);
            return Response(true, is_picked_up);
        }
        return Response(true, NO_ITEM_PICKED_UP_MSG);
    } else {
        return Response(true, NO_ITEM_PICKED_UP_MSG);
    }
}