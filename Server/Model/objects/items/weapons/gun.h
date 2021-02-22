#ifndef GUN_H_
#define GUN_H_

#include "weapon.h"

class Gun: public Weapon {
 public:
    Gun();
    ~Gun();
    void attack(double& distance, int& damage) override;
    const int getType() override;
};

#endif // GUN_H_
