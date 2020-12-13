#include "gun.h"

Gun::Gun() {
    this->precision = GUN_PRECISION;
    this->probability_accuracy = GUN_ACCURACY;
    this->probabiliy_damage = GUN_DAMAGE;

    this->bullets_blast = GUN_BULLETS_BLAST;
    this->period_blast = GUN_PERIOD_BLAST;
}

float Gun::attack(int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    float rd_num = getRandomNumber();
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

int Gun::getType() {
    return GUN_TYPE;
}