#include "./player_info.h"
#include "../constants/config.h"
#include <algorithm>

PlayerInfo::PlayerInfo() {
    
    this->bullets = 0;
    this->life = MAX_LIFE;
    this->keys = 0;
    this->treasure = 0;
    this->resurrected = 0;
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
    this->treasure += treasure;
}

void PlayerInfo::addNumResurrection() {
    this->resurrected += 1;
}

std::list <Weapon*> PlayerInfo::getInventory() {
    return this->inventory;
}

void PlayerInfo::addInventory(Weapon* &weapon) {
    this->inventory.push_back(weapon);
}

bool PlayerInfo::hasWeapon(Weapon* &weapon) {
    return (std::find(this->inventory.begin(), this->inventory.end(), weapon) != this->inventory.end());
}
