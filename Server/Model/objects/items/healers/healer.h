#ifndef HEALER_H_
#define HEALER_H_

#include "../item.h"

class Healer: public Item {
   public:
      Healer();
      int heal() override;
      virtual int getItemType() = 0;
      int getPoints() override; //treaure
      void attack(double& distance, int& damage) override; //weapon
      int getType() override; //weapon
      int getBullets() override;//bullets
 protected:
    int points;
};

#endif    // HEALER_H_
