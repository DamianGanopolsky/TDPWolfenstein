#ifndef ROCKET_LAUNCHER_H_
#define ROCKET_LAUNCHER_H_

#include "ranged_weapon.h"

class RocketLauncher: public RangedWeapon {
 public:
    RocketLauncher();
    float attack(int& damage) override;
    int getType() override;
};

#endif   // ROCKET_LAUNCHER_H_
