#include "./command_pick_up.h"

CommandPickUp::CommandPickUp(){}

bool CommandPickUp::pickUp(PlayerInfo &info, Item &item) {
    return true;
}
bool CommandPickUp::pickUp(PlayerInfo &info, Bullet &item) {
    if (info.getNumBullets() < MAX_BULLETS) {
        info.addBullets(item.getBullets());
        return true;
    }
    return false;
}

bool CommandPickUp::pickUp(PlayerInfo &info, Food &item) {
    if (info.getLife() < MAX_LIFE) {
        info.addLife(item.heal());
        return true;
    }
    return false;
}

bool CommandPickUp::pickUp(PlayerInfo &info, Kit &item) {
    if (info.getLife() < MAX_LIFE) {
        info.addLife(item.heal());
        return true;
    }
    return false;
}

bool CommandPickUp::pickUp(PlayerInfo &info, Blood &item) {
    if (info.getLife() < BLOOD_MINIMUN_TO_HEAL) {
        info.addLife(item.heal());
        return true;
    }
    return false;
}

bool CommandPickUp::pickUp(PlayerInfo &info, Key &item) {
    info.addNumKeys(1);
    return true;
}

bool CommandPickUp::pickUp(PlayerInfo &info, Treasure &item) {
    info.addTreasure(item.getPoints());
    return true;
}
/*

bool CommandPickUp::pickUp(Weapon &item) {
    if(info.hasWeapon(item)){
        return false;
    }
    info.addInventory(item);
    return true;
}
*/