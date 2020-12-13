#ifndef GUN_H_
#define GUN_H_

#include "ranged_weapon.h"

class Gun: public RangedWeapon {
 public:
    Gun();
    float attack(int& damage) override;
    int getType() override;
};

#endif // GUN_H_
