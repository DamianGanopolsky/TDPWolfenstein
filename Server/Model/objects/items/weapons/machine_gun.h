#ifndef MACHINE_GUN_H_
#define MACHINE_GUN_H_

#include "weapon.h"

class MachineGun: public Weapon {
 public:
    MachineGun();
    ~MachineGun();
    void attack(double& distance, int& damage) override;
    const int getType() override;
};

#endif   // MACHINE_GUN_H_
