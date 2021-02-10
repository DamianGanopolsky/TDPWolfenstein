#include "./player_info.h"
#include "../constants/config.h"
#include "../objects/items/weapons/gun.h"
#include "../objects/items/weapons/knife.h"
#include <algorithm>
#include <iostream>

PlayerInfo::PlayerInfo() : life(50), bullets(8),
                            keys(0), treasure(0), 
                            resurrected(10) {
                                Gun gun;
                                this->equiped = &gun;
                                this->inventory.push_back(GUN_TYPE);
                                this->inventory.push_back(KNIFE_TYPE);
                            }

PlayerInfo::~PlayerInfo(){}

int PlayerInfo::getLife() {
    return this->life;
}

int PlayerInfo::getNumBullets() {
    std::cout <<"GET bullets: "<<this->bullets<<std::endl;
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

/*void PlayerInfo::reduceLife(int item_life) {
    this->life -= item_life;
    this->life = (this->life < 0) ? 0 : this->life;
}

void PlayerInfo::reduceBullets(int item_bullets) {
    this->bullets -= item_bullets;
    this->bullets = (this->bullets < 0) ? 0 : this->bullets;
}

void PlayerInfo::reduceNumKeys(int item_key) {
    this->keys -= item_key;
    this->keys = (this->keys < 0) ? 0 : this->keys;
}

void PlayerInfo::reduceTreasure(int item_treasure) {
    this->treasure -= item_treasure;
    this->treasure = (this->treasure < 0) ? 0 : this->treasure;
}

void PlayerInfo::changeWeaponEquiped(Weapon* &weapon) {
    this->equiped = weapon;
}

void PlayerInfo::addLife(int item_life) {
    this->life += item_life;
    this->life = (this->life > MAX_LIFE) ? MAX_LIFE : this->life;
}

void PlayerInfo::addBullets(int item_bullets) {
    std::cout <<"agrego bullets: "<<item_bullets<<std::endl;
    this->bullets += item_bullets;
    std::cout <<"bullets: "<<this->bullets<<std::endl;
    this->bullets = (this->bullets > MAX_BULLETS) ? MAX_BULLETS : this->bullets;
    std::cout <<"bullets: "<<this->bullets<<std::endl;
}

void PlayerInfo::addNumKeys(int item_key) {
    this->keys += item_key;
}

void PlayerInfo::addTreasure(int item_treasure) {
    this->treasure += item_treasure;
}

void PlayerInfo::addNumResurrection() {
    this->resurrected += 1;
}


void PlayerInfo::changeWeaponEquiped(Weapon* &weapon) {
    this->equiped = weapon;
}
*/
std::list <int> PlayerInfo::getInventory() {
    return this->inventory;
}

/*void PlayerInfo::addInventory(int weapon) {
    this->inventory.push_back(weapon);
}*/

bool PlayerInfo::hasWeapon(int weapon) {
    std::cout << "PlayerInfo: has weapon" <<std::endl;
    return (std::find(this->inventory.begin(), this->inventory.end(), weapon) != this->inventory.end());
    /*std::cout << "PlayerInfo: iterator" <<std::endl;
    if (weapon == nullptr) {
        std::cout << "PlayerInfo: null weapon" <<std::endl;
    }
    int type = weapon->getType();
    std::cout << "PlayerInfo: type" <<std::endl;
    it = this->inventory.find(type);
    std::cout << "PlayerInfo: find weapon" <<std::endl;
    if (it == inventory.end()) {
        std::cout << "PlayerInfo: no weapon" <<std::endl;
        return false;
    } else {
        std::cout << "PlayerInfo: weapon" <<std::endl;
        return true;
    }*/
}
