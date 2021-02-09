#include "./player_info.h"
#include "../constants/config.h"
#include "../objects/items/weapons/gun.h"
#include "../objects/items/weapons/knife.h"
#include <algorithm>
#include <iostream>

PlayerInfo::PlayerInfo() : life(MAX_LIFE), bullets(8),
                            keys(0), treasure(0), 
                            resurrected(10) {
                                Gun gun;
                                this->equiped = &gun;
                                this->inventory.emplace(gun.getType(), &gun);
                                Knife knife;
                                this->inventory.emplace(knife.getType(), &knife);
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

void PlayerInfo::reduceLife(int life) {
    this->life -= life;
    this->life = (this->life < 0) ? 0 : this->life;
}

void PlayerInfo::reduceBullets(int bullets) {
    this->bullets -= bullets;
    this->bullets = (this->bullets < 0) ? 0 : this->bullets;
}

void PlayerInfo::reduceNumKeys(int key) {
    this->keys -= key;
    this->keys = (this->keys < 0) ? 0 : this->keys;
}

void PlayerInfo::reduceTreasure(int treasure) {
    this->treasure -= treasure;
    this->treasure = (this->treasure < 0) ? 0 : this->treasure;
}

void PlayerInfo::changeWeaponEquiped(Weapon* &weapon) {
    this->equiped = weapon;
}

void PlayerInfo::addLife(int life) {
    this->life += life;
    this->life = (this->life > MAX_LIFE) ? MAX_LIFE : this->life;
}

void PlayerInfo::addBullets(int bullets) {
    this->bullets += bullets;
    this->bullets = (this->bullets > MAX_BULLETS) ? MAX_BULLETS : this->bullets;
}

void PlayerInfo::addNumKeys(int key) {
    this->keys += key;
}

void PlayerInfo::addTreasure(int treasure) {
    this->treasure = this->treasure + treasure;
}

void PlayerInfo::addNumResurrection() {
    this->resurrected += 1;
}

std::unordered_map <int, Weapon*> PlayerInfo::getInventory() {
    return this->inventory;
}

void PlayerInfo::addInventory(Weapon* &weapon) {
    this->inventory.emplace(weapon->getType(), weapon);
}

bool PlayerInfo::hasWeapon(Weapon* &weapon) {
    if (weapon == nullptr) {std::cout << "PlayerInfo: null weapon" <<std::endl;}
    std::cout << "PlayerInfo: has weapon" <<std::endl;
    std::unordered_map<int, Weapon*>::iterator it;
    std::cout << "PlayerInfo: iterator" <<std::endl;
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
    }
}
