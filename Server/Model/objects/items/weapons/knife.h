#ifndef KNIFE_H_
#define KNIFE_H_

#include "weapon.h"

class Knife: public Weapon {
    int bullets_blast;
    float period_blast;
    static bool inRange();
 public:
    Knife();
    void attack(int& damage) override;
    int getType() override;
};

#endif   // KNIFE_H_
