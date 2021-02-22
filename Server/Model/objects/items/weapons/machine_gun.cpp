#include "machine_gun.h"

MachineGun::MachineGun(){}

MachineGun::~MachineGun() {}

void MachineGun::attack(double& distance, int& damage) {
    if(distance<70){
        damage = GameConfig.machine_gun_base_damage;
    }
    else if(distance<400){
        damage = GameConfig.machine_gun_base_damage-GameConfig.machine_gun_base_damage/4 ;
    }
    else{
        damage = GameConfig.machine_gun_base_damage/2;
    }
}

const int MachineGun::getType() {
    return MACHINE_GUN_TYPE;
}