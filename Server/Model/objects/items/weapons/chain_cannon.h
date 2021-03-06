#ifndef CHAIN_CANNON_H_
#define CHAIN_CANNON_H_

#include "weapon.h"

class ChainCannon: public Weapon {
 public:
    ChainCannon();
    ~ChainCannon();
    void attack(double& distance, int& damage) override;
    const int getType() override;
};

#endif   // CHAIN_CANNON_H_
