#ifndef CHAIN_CANNON_H_
#define CHAIN_CANNON_H_

#include "ranged_weapon.h"

class ChainCannon: public RangedWeapon {
 public:
    ChainCannon();
    float attack(int& damage) override;
    int getType() override;
};

#endif   // CHAIN_CANNON_H_
