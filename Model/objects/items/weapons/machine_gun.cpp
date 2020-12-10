#include "machine_gun.h"

MachineGun::MachineGun(){
    this->precision = MACHINE_GUN_PRECISION;
    this->probability_accuracy = MACHINE_GUN_ACCURACY;
    this->probabiliy_damage = MACHINE_GUN_DAMAGE;

    this->bullets_blast = MACHINE_GUN_BULLETS_BLAST;
    this->bullets_blast = MACHINE_GUN_PERIOD_BLAST;
}

float MachineGun::attack(int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    float rd_num = getRandomNumber();
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

int MachineGun::getType() {
    return MACHINE_GUN_TYPE;
}