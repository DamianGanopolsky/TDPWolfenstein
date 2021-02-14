#include "chain_cannon.h"

ChainCannon::ChainCannon(){
    this->bullets_blast = CHAIN_CANNON_BULLETS_BLAST;
    this->period_blast = CHAIN_CANNON_PERIOD_BLAST;
}

ChainCannon::~ChainCannon() {}

void ChainCannon::attack(double& distance, int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    /*float rd_num = getRandomNumber();
    int precision = 0 ;
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }*/
    damage = 40;
}

const int ChainCannon::getType() {
    return CHAIN_CANNON_TYPE;
}