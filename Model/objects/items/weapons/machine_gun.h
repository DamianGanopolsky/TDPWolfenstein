#ifndef MACHINE_GUN_H_
#define MACHINE_GUN_H_

#include "ranged_weapon.h"

class MachineGun: public RangedWeapon {
 public:
    MachineGun();
    float attack(int& damage) override;
    int getType() override;
};

#endif   // MACHINE_GUN_H_
