#ifndef BULLET_H_
#define BULLET_H_

#include "./../item.h"

class Bullet: public Item {
   public:
      explicit Bullet();
      int getBullets() override;
      int getItemType() override;
      int getPoints() override; //treaure
      void attack(double& distance, int& damage) override; //weapon
      const int getType() override; //weapon
      int heal() override;//healer

   private:
      int num_bullet;
};

#endif    // BULLET_H_
