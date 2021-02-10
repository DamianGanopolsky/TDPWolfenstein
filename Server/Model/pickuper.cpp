#include "pickuper.h"

PickUp::PickUp() {}

PickUp::~PickUp () {}

int PickUp::pickUp(Player& player, Item* item) {
    std::cout<<"pickup Object"<<std::endl;
    switch (item->getItemType()) {
        case BULLETS: {
            std::cout <<"BULLETS!"<<std::endl;
            if (player.getInfo().getNumBullets() < MAX_BULLETS) {
                player.addBullets(item->getBullets());
                std::cout <<player.getInfo().getNumBullets()<<std::endl;
                return BULLETS_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case FOOD: {
            std::cout <<"FOOD!"<<std::endl;
            if (player.getInfo().getLife() < MAX_LIFE) {
                player.addLife(item->heal());
                return FOOD_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case KIT: {
            std::cout <<"KIT!"<<std::endl;
            if (player.getInfo().getLife() < MAX_LIFE) {
                player.addLife(item->heal());
                return MEDICAL_KIT_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case BLOOD: {
            std::cout <<"BLOOD!"<<std::endl;
            if (player.getInfo().getLife() < BLOOD_MINIMUN_TO_HEAL) {
                player.addLife(item->heal());
                return BLOOD_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case KEY: {
            std::cout <<"KEY!"<<std::endl;
            player.addNumKeys(1);
            return KEY_TAKEN_ITM;
        }
        case TREASURE: {
            std::cout <<"TREASURE!"<<std::endl;
            std::cout <<"Points: "<< item->getPoints() <<std::endl;
            player.addTreasure(item->getPoints());
            return TREASURE_TAKEN_ITM;
        }
        case WEAPON: {
            std::cout <<"WEAPON!"<<std::endl;
            std::cout <<"wepon type: "<< item->getType() <<std::endl;
            if(player.getInfo().hasWeapon(item->getType())) {
                std::cout <<"has weapon"<<std::endl;
                return NO_ITEM_PICKED_UP;
            }
            std::cout <<"doesnt has weapon"<<std::endl;
            player.addInventory(item->getType());
            std::cout <<"weapon added"<<std::endl;
            return WEAPON_TAKEN_ITM;
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
