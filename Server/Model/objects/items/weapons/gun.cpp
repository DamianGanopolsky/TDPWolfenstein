#include "gun.h"

Gun::Gun() {}

Gun::~Gun() {}

void Gun::attack(double& distance, int& damage) {
    if(distance<70){
        damage = GameConfig.gun_base_damage;
    }
    else{
        damage = GameConfig.gun_base_damage/2;
    }
}

const int Gun::getType() {
    return GUN_TYPE;
}