#include "./pick_up.h"

PickUp::PickUp(PlayerInfo &info) {
    this->info = info;
}

bool PickUp::pickUp(Bullet &item) {
    if (this->info.getNumBullets() < MAX_BULLETS) {
        this->info.addBullets(item.getBullets());
        return true;
    }
    return false;
}

bool PickUp::pickUp(Food &item) {
    if (this->info.getLife() < MAX_LIFE) {
        this->info.addLife(item.heal());
        return true;
    }
    return false;
}

bool PickUp::pickUp(Kit &item) {
    if (this->info.getLife() < MAX_LIFE) {
        this->info.addLife(item.heal());
        return true;
    }
    return false;
}

bool PickUp::pickUp(Blood &item) {
    if (this->info.getLife() < BLOOD_MINIMUN_TO_HEAL) {
        this->info.addLife(item.heal());
        return true;
    }
    return false;
}

bool PickUp::pickUp(Key &item) {
    this->info.addNumKeys(1);
    return true;
}

bool PickUp::pickUp(Treasure &item) {
    this->info.addTreasure(item.getPoints());
    return true;
}

bool PickUp::pickUp(Weapon &item) {
    if(this->info.hasWeapon(item)){
        return false;
    }
    this->info.addInventory(item);
    return true;
}
