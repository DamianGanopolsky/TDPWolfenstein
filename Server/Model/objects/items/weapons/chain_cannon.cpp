#include "chain_cannon.h"

ChainCannon::ChainCannon(){
    this->bullets_blast = CHAIN_CANNON_BULLETS_BLAST;
    this->period_blast = CHAIN_CANNON_PERIOD_BLAST;
}

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