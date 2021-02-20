#include "machine_gun.h"

MachineGun::MachineGun(){
    this->bullets_blast = MACHINE_GUN_BULLETS_BLAST;
    this->period_blast = MACHINE_GUN_PERIOD_BLAST;
}

MachineGun::~MachineGun() {}
//ESTE ATTACK CAMBIA EL DAÑO
void MachineGun::attack(double& distance, int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    /*float rd_num = getRandomNumber();
    int precision = 0 ;
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }*/
    //damage = 5;
    if(distance<70){
        damage = GameConfig.machine_gun_base_damage;
    }
    else if(distance<400){
        damage = GameConfig.machine_gun_base_damage-GameConfig.machine_gun_base_damage/4 ;
    }
    else{
        damage = GameConfig.machine_gun_base_damage/2;
    }
    //damage=GameConfig.machine_gun_base_damage;
}

const int MachineGun::getType() {
    return MACHINE_GUN_TYPE;
}