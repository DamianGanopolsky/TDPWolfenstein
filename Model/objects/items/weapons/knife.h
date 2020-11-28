#ifndef KNIFE_H_
#define KNIFE_H_

#include "contact_weapon.h"

class Knife: public ContactWeapon {
 public:
    Knife();
    float attack() override;
};

#endif   // KNIFE_H_
