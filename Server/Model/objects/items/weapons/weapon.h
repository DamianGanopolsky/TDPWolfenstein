#ifndef WEAPON_H_
#define WEAPON_H_

#include <random>

#include "./../item.h"

class Weapon: public Item {
 public:
   Weapon();
   virtual ~Weapon();
   virtual void attack(double& distance, int& damage) = 0;
   virtual int getType() = 0;
   static float getRandomNumber();
};

#endif   // WEAPON_H_
