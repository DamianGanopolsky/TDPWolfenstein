#include "chain_cannon.h"

ChainCannon::ChainCannon(){
    this->precision = CHAIN_CANNON_PRECISION;
    this->probability_accuracy = CHAIN_CANNON_ACCURACY;
    this->probabiliy_damage = CHAIN_CANNON_DAMAGE;

    this->bullets_blast = CHAIN_CANNON_BULLETS_BLAST;
    this->bullets_blast = CHAIN_CANNON_PERIOD_BLAST;
}

float ChainCannon::attack(int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    float rd_num = getRandomNumber();
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

int ChainCannon::getType() {
    return CHAIN_CANNON_TYPE;
}