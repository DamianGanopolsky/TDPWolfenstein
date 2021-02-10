#ifndef WEAPON_H_
#define WEAPON_H_

#include <random>

#include "./../item.h"

class Weapon: public Item {
  public:
    Weapon();
    virtual ~Weapon();
    virtual void attack(double& distance, int& damage) = 0;
    virtual const int getType() = 0;
    static float getRandomNumber();
    int getItemType() override;
    int getPoints() override; //treaure
    int heal() override;//healer
    int getBullets() override;//bullets
};

#endif   // WEAPON_H_
