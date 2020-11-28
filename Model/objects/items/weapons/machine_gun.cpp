#include "machine_gun.h"

MachineGun::MachineGun(){
    this->precision = MACHINE_GUN_PRECISION;
    this->probability_accuracy = MACHINE_GUN_ACCURACY;
    this->probabiliy_damage = MACHINE_GUN_DAMAGE;

    this->bullets_blast = MACHINE_GUN_BULLETS_BLAST;
    this->bullets_blast = MACHINE_GUN_PERIOD_BLAST;
}