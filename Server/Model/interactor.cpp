#include "interactor.h"
#include "./constants/const_object_map.h"

Interact::Interact() {}

Interact::~Interact() {}

/*Response Interact::interactWith(Player &player, Map& map, BlockingObject &obj) {
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
}*/

Response Interact::interactWith(Player &player, Map& map, Object* object) {
    std::cout <<"Interact: interacting"<< std::endl;
    if (object->isBlocking()) {
        std::cout <<"Interact: is blocking"<< std::endl;
        return Response(false, NO_ITEM_PICKED_UP_MSG);
    } else if (object->isItem()) {
        std::cout <<"Interact: is item"<< std::endl;
        PlayerInfo pi = player.getInfo();
        PickUp pickuper;
        Response is_picked_up = pickuper.pickUp(pi, object);
        if (is_picked_up.success) {
            std::cout <<"Interact: success picking up"<< std::endl;
            PlayerPosition pos = player.getPos();
            map.setObjectPos(pos.getX(), pos.getY(), MAP_NONE);
            Response(true, is_picked_up.message);
        }
        return Response(true, NO_ITEM_PICKED_UP_MSG);
    } else {
        std::cout <<"Interact: is non blocking"<< std::endl;
        return Response(true, NO_ITEM_PICKED_UP_MSG);
    }
    //return Response(true, NO_ITEM_PICKED_UP_MSG);
}