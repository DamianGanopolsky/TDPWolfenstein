#include "./player_info.h"
#include "./../objects/items/weapons/knife.h"

PlayerInfo::PlayerInfo() {
    this->bullets = MAX_BULLETS;
    this->life = MAX_LIFE;
    this->keys = 0;
    Knife knife;
    this->inventory.insert(knife);
}

int PlayerInfo::getLife() {
    return this->life;
}

int PlayerInfo::getNumBullets() {
    return this->bullets;
}

int PlayerInfo::getKey() {
    int num = 0;
    if(this->keys > 0){
        --this->keys;
        num = 1;   
    }
    return num;
}

/*
int PlayerInfo::getInventory() {
    return this->inventory;
}
*/

void PlayerInfo::addLife(int life) {
    this->life += life;
    this->life = (this->life > MAX_LIFE) ? MAX_LIFE : this->life;
}

void PlayerInfo::addBullets(int bullets) {
    this->bullets += bullets;
    this->life = (this->life > MAX_BULLETS) ? MAX_BULLETS : this->life;
}

void PlayerInfo::addNumKeys(int key) {
    this->keys += key;
}

void PlayerInfo::addTreasure(int treasure) {
    this->treasure += treasure;
}

void PlayerInfo::addInventory(Weapon &weapon) {
    this->inventory.insert(weapon);
}

bool PlayerInfo::hasWeapon(Weapon &weapon) {
    return this->inventory.find(weapon) == this->inventory.end();
}

PlayerInfo::~PlayerInfo(){}