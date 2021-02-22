#ifndef KNIFE_H_
#define KNIFE_H_

#include "weapon.h"

class Knife: public Weapon {
    static bool _inRange();
 public:
    Knife();
    ~Knife();
    void attack(double& distance, int& damage) override;
    const int getType() override;
};

#endif   // KNIFE_H_
