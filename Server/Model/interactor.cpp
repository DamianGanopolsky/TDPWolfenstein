#include "interactor.h"
#include "./constants/const_object_map.h"

Interact::Interact() {}

Interact::~Interact() {}

Response Interact::interactWith(Player &player, Map& map, Object* object) {
    std::cout <<"Interact: interacting"<< std::endl;
    if (object->isBlocking()) {
        std::cout <<"Interact: is blocking"<< std::endl;
        return Response(false, NO_ITEM_PICKED_UP_MSG);
    } else if (object->isItem()) {
        std::cout <<"Interact: is item"<< std::endl;
        PickUp pickuper;
        int is_picked_up = pickuper.pickUp(player, object->getItem());
        if (is_picked_up != NO_ITEM_PICKED_UP) {
            std::cout <<"Interact: success picking up"<< std::endl;
            PlayerPosition pos = player.getPos();
            map.setObjectPos(pos.getX(), pos.getY(), MAP_NONE);
            return Response(true, is_picked_up);
        }
        return Response(true, NO_ITEM_PICKED_UP_MSG);
    } else {
        std::cout <<"Interact: is non blocking"<< std::endl;
        return Response(true, NO_ITEM_PICKED_UP_MSG);
    }
}