#ifndef TREASURE_H
#define TREASURE_H

#include "./../item.h"

class Treasure: public Item  {
   public:
      int getPoints() override;
      int getItemType() override;
      void attack(double& distance, int& damage) override; //weapon
      int getType() override; //weapon
      int heal() override;//healer
      int getBullets() override;//bullets
   protected:
      int points;
};

#endif    // TREASURE_H
