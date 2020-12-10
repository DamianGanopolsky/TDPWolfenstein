#ifndef WEAPON_H_
#define WEAPON_H_

#include <random>

#include "./../item.h"

class Weapon: public Item {
 protected:
    float precision;
    float probability_accuracy;
    float probabiliy_damage;
 public:
   Weapon();
   virtual float attack(int& damage);
   virtual int getType();
   virtual ~Weapon();
   static float getRandomNumber();
};

#endif   // WEAPON_H_
