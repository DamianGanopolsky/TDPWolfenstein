#ifndef RANGED_WEAPON_H_
#define RANGED_WEAPON_H_

#include "weapon.h"

class RangedWeapon: public Weapon {
 public:
    RangedWeapon() {}
    virtual int getType() = 0;
 protected:
    int bullets_blast;
    float period_blast;
};

#endif   // RANGED_WEAPON_H_
