#include "pickuper.h"

PickUp::PickUp() {}

PickUp::~PickUp () {}

int PickUp::pickUp(PlayerInfo &info, Item* item) {
    std::cout<<"pickup Object"<<std::endl;
    switch (item->getItemType()) {
        case BULLETS: {
            if (info.getNumBullets() < MAX_BULLETS) {
                info.addBullets(item->getBullets());
                return BULLETS_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case FOOD: {
            if (info.getLife() < MAX_LIFE) {
                info.addLife(item->heal());
                return FOOD_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case KIT: {
            if (info.getLife() < MAX_LIFE) {
                info.addLife(item->heal());
                return MEDICAL_KIT_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case BLOOD: {
            if (info.getLife() < BLOOD_MINIMUN_TO_HEAL) {
                info.addLife(item->heal());
                return BLOOD_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case KEY: {
            info.addNumKeys(1);
            return KEY_TAKEN_ITM;
        }
        case TREASURE: {
            std::cout <<"TREASURE!"<<std::endl;
            std::cout <<"Points: "<< item->getPoints() <<std::endl;
            info.addTreasure(item->getPoints());
            return TREASURE_TAKEN_ITM;
        }
        case WEAPON: {
            /*if(info.hasWeapon(item)) {
                return NO_ITEM_PICKED_UP;
            }
            info.addInventory(item);
            return WEAPON_TAKEN_ITM;*/
            break;
        }
    }
    return NO_ITEM_PICKED_UP;
}

/*int PickUp::pickUp(PlayerInfo &info, Bullet &item) {
    if (info.getNumBullets() < MAX_BULLETS) {
        info.addBullets(item.getBullets());
        return BULLETS_TAKEN_ITM;
    }
    return NO_ITEM_PICKED_UP;
}

int PickUp::pickUp(PlayerInfo &info, Food &item) {
    if (info.getLife() < MAX_LIFE) {
        info.addLife(item.heal());
        return FOOD_TAKEN_ITM;
    }
    return NO_ITEM_PICKED_UP;
}

int PickUp::pickUp(PlayerInfo &info, Kit &item) {
    if (info.getLife() < MAX_LIFE) {
        info.addLife(item.heal());
        return MEDICAL_KIT_TAKEN_ITM;
    }
    return NO_ITEM_PICKED_UP;
}

int PickUp::pickUp(PlayerInfo &info, Blood &item) {
    if (info.getLife() < BLOOD_MINIMUN_TO_HEAL) {
        info.addLife(item.heal());
        return BLOOD_TAKEN_ITM;
    }
    return NO_ITEM_PICKED_UP;
}

int PickUp::pickUp(PlayerInfo &info, Key &item) {
    info.addNumKeys(1);
    return KEY_TAKEN_ITM;
}

int PickUp::pickUp(PlayerInfo &info, Treasure &item) {
    info.addTreasure(item.getPoints());
    return TREASURE_TAKEN_ITM;
}

int PickUp::pickUp(PlayerInfo &info, Weapon* item) {
    if(info.hasWeapon(item)){
        return NO_ITEM_PICKED_UP;
    }
    info.addInventory(item);
    return WEAPON_TAKEN_ITM;
}*/
