#include "machine_gun.h"

MachineGun::MachineGun(){
    this->bullets_blast = MACHINE_GUN_BULLETS_BLAST;
    this->period_blast = MACHINE_GUN_PERIOD_BLAST;
}

void MachineGun::attack(double& distance, int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    float rd_num = getRandomNumber();
    int precision = 0 ;
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

int MachineGun::getType() {
    return MACHINE_GUN_TYPE;
}