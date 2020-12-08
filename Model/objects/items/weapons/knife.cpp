#include "knife.h"

Knife::Knife() {
    this->precision = GUN_PRECISION;
    this->probability_accuracy = GUN_ACCURACY;
    this->probabiliy_damage = GUN_DAMAGE;
}

float Knife::attack(int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    float rd_num = getRandomNumber();
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

int Knife::getType() {
    return KNIFE_TYPE;
}