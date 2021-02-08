#ifndef ROCKET_LAUNCHER_H_
#define ROCKET_LAUNCHER_H_

#include "weapon.h"

class RocketLauncher: public Weapon {
    int bullets_blast;
    float period_blast;
 public:
    RocketLauncher();
    void attack(double& distance, int& damage) override;
    int getType() override;
};

#endif   // ROCKET_LAUNCHER_H_
