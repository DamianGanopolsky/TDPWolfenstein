#include "chain_cannon.h"

ChainCannon::ChainCannon(){}

ChainCannon::~ChainCannon() {}

void ChainCannon::attack(double& distance, int& damage) {
    if(distance<70){
        damage = GameConfig.chain_cannon_base_damage;
    }
    else if(distance<400){
        damage = GameConfig.chain_cannon_base_damage-GameConfig.chain_cannon_base_damage/4 ;
    }
    else{
        damage = GameConfig.chain_cannon_base_damage/2;
    }
}

const int ChainCannon::getType() {
    return CHAIN_CANNON_TYPE;
}