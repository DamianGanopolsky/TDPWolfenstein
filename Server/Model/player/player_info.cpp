#include "./player_info.h"
#include "../constants/config.h"

#include <algorithm>
#include <iostream>

PlayerInfo::PlayerInfo() : life(50), bullets(100),
                            keys(0), treasure(0), 
                            resurrected(0) {
                                this->weapon_type.insert(std::make_pair<Weapon*, int>(&knife, KNIFE_TYPE));
                                this->weapon_type.insert(std::make_pair<Weapon*, int>(&gun, GUN_TYPE));
                                this->weapon_type.insert(std::make_pair<Weapon*, int>(&machine_gun, MACHINE_GUN_TYPE));
                                this->weapon_type.insert(std::make_pair<Weapon*, int>(&chain_cannon, CHAIN_CANNON_TYPE));
                                this->equiped = &gun;
                                this->inventory.push_back(GUN_TYPE);
                                this->inventory.push_back(KNIFE_TYPE);
                                this->inventory.push_back(MACHINE_GUN_TYPE);
                                this->inventory.push_back(CHAIN_CANNON_TYPE);
                            }

PlayerInfo::~PlayerInfo(){}

int PlayerInfo::getLife() {
    return this->life;
}

int PlayerInfo::getNumBullets() {
    return this->bullets;
}

int PlayerInfo::getKey() {
    return this->keys;
}

int PlayerInfo::getTreasure() {
    return this->treasure;
}

int PlayerInfo::getNumResurrection() {
    return this->resurrected;
}

Weapon* PlayerInfo::getWeaponEquiped() {
    return this->equiped;
}

int PlayerInfo::getWeaponTypeEquiped() {
    std::cout << "PlayerInfo: getWeaponTypeEquiped()"<<std::endl;
    switch (this->weapon_type.at(this->equiped)) {
        case KNIFE_TYPE: {
            std::cout << "PlayerInfo: knife"<<std::endl;
            return KNIFE_TYPE;
        }
        case GUN_TYPE: {
            std::cout << "PlayerInfo: gun"<<std::endl;
            return GUN_TYPE;
        }
        case MACHINE_GUN_TYPE: {
            std::cout << "PlayerInfo: machine_gun"<<std::endl;
            return MACHINE_GUN_TYPE;
        }
        case CHAIN_CANNON_TYPE: {
            std::cout << "PlayerInfo: chain_cannon"<<std::endl;
            return CHAIN_CANNON_TYPE;
        }
        default:
            break;
    }
    return -1;
}

std::list <int> PlayerInfo::getInventory() {
    return this->inventory;
}

void PlayerInfo::changeWeaponEquiped(int& type) {
    for (auto& x: weapon_type) {
        if (x.second == type) {
            this->equiped = x.first;
        }
    }
}

bool PlayerInfo::hasWeapon(int weapon) {
    std::cout << "PlayerInfo: has weapon" <<std::endl;
    return (std::find(this->inventory.begin(), this->inventory.end(), weapon) != this->inventory.end());
}
