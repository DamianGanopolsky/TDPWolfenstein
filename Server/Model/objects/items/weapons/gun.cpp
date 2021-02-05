#include "gun.h"

Gun::Gun() {
    this->bullets_blast = GUN_BULLETS_BLAST;
    this->period_blast = GUN_PERIOD_BLAST;
}

void Gun::attack(int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    float rd_num = getRandomNumber();
    int precision = 0 ;
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

int Gun::getType() {
    return GUN_TYPE;
}