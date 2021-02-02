#include "pickuper.h"

PickUp::PickUp() {}

PickUp::~PickUp () {}

Response PickUp::pickUp(PlayerInfo &info, Item &item) {
    return Response(true, ITEM_PICKED_UP_MSG);
}
Response PickUp::pickUp(PlayerInfo &info, Bullet &item) {
    if (info.getNumBullets() < MAX_BULLETS) {
        info.addBullets(item.getBullets());
        return Response(true, BULLETS_PICKED_UP_MSG);
    }
    return Response(false, NO_ITEM_PICKED_UP_MSG);
}

Response PickUp::pickUp(PlayerInfo &info, Food &item) {
    if (info.getLife() < MAX_LIFE) {
        info.addLife(item.heal());
        return Response(true, FOOD_PICKED_UP_MSG);
    }
    return Response(false, NO_ITEM_PICKED_UP_MSG);
}

Response PickUp::pickUp(PlayerInfo &info, Kit &item) {
    if (info.getLife() < MAX_LIFE) {
        info.addLife(item.heal());
        return Response(true, KIT_PICKED_UP_MSG);
    }
    return Response(false, NO_ITEM_PICKED_UP_MSG);
}

Response PickUp::pickUp(PlayerInfo &info, Blood &item) {
    if (info.getLife() < BLOOD_MINIMUN_TO_HEAL) {
        info.addLife(item.heal());
        return Response(true, BLOOD_PICKED_UP_MSG);
    }
    return Response(false, NO_ITEM_PICKED_UP_MSG);
}

Response PickUp::pickUp(PlayerInfo &info, Key &item) {
    info.addNumKeys(1);
    return Response(true, KEY_PICKED_UP_MSG);
}

Response PickUp::pickUp(PlayerInfo &info, Treasure &item) {
    info.addTreasure(item.getPoints());
    return Response(true, TREASURE_PICKED_UP_MSG);
}

Response PickUp::pickUp(PlayerInfo &info, Weapon* item) {
    if(info.hasWeapon(item)){
        return Response(false, NO_ITEM_PICKED_UP_MSG);
    }
    info.addInventory(item);
    return Response(true, WEAPON_PICKED_UP_MSG);
}
