#ifndef CHAIN_CANNON_H_
#define CHAIN_CANNON_H_

#include "weapon.h"

class ChainCannon: public Weapon {
    int bullets_blast;
    float period_blast;
 public:
    ChainCannon();
    void attack(double& distance, int& damage) override;
    int getType() override;
};

#endif   // CHAIN_CANNON_H_
