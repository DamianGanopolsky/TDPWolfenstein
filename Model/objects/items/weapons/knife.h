#ifndef KNIFE_H_
#define KNIFE_H_

#include "contact_weapon.h"

class Knife: public ContactWeapon {
 public:
    Knife();
    float attack(int& damage) override;
    int getType() override;
};

#endif   // KNIFE_H_
