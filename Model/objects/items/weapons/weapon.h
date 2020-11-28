#ifndef WEAPON_H_
#define WEAPON_H_

#include "./../item.h"

class Weapon: public Item {
 protected:
    float precision;
    float probability_accuracy;
    float probabiliy_damage;
 public:
   Weapon();
    virtual float attack();
};

#endif   // WEAPON_H_
