#ifndef GUN_H_
#define GUN_H_

#include "weapon.h"

class Gun: public Weapon {
    int bullets_blast;
    float period_blast;
 public:
    Gun();
    void attack(double& distance, int& damage) override;
    int getType() override;
};

#endif // GUN_H_
