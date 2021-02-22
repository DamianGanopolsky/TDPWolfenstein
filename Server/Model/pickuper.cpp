#include "pickuper.h"

#define BLOOD_MINIMUN_TO_HEAL 11

PickUp::PickUp() {}

PickUp::~PickUp () {}

int PickUp::pickUp(Player& player, Item* item) {
    switch (item->getItemType()) {
        case BULLETS: {
            if (player.getInfo().getNumBullets() < GameConfig.max_bullets) {
                player.addBullets(item->getBullets());
                std::cout <<player.getInfo().getNumBullets()<<std::endl;
                return BULLETS_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case FOOD: {
            if (player.getInfo().getLife() < GameConfig.max_life) {
                player.addLife(item->heal());
                return FOOD_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case KIT: {
            if (player.getInfo().getLife() < GameConfig.max_life) {
                player.addLife(item->heal());
                return MEDICAL_KIT_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case BLOOD: {
            if (player.getInfo().getLife() < BLOOD_MINIMUN_TO_HEAL) {
                player.addLife(item->heal());
                return BLOOD_TAKEN_ITM;
            }
            return NO_ITEM_PICKED_UP;
        }
        case KEY: {
            player.addNumKeys(1);
            return KEY_TAKEN_ITM;
        }
        case TREASURE: {
            player.addTreasure(item->getPoints());
            return TREASURE_TAKEN_ITM;
        }
        case WEAPON: {
            if(player.getInfo().hasWeapon(item->getType())) {;
                return NO_ITEM_PICKED_UP;
            }
            player.addInventory(item->getType());
            return WEAPON_TAKEN_ITM;
            break;
        }
    }
    return NO_ITEM_PICKED_UP;
}
