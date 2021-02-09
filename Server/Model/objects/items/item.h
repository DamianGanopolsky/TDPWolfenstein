#ifndef ITEM_H_
#define ITEM_H_

#include "./../../constants/config.h"
#include "./../object.h"

class Item: public Object {
   public:
      Item();
      virtual ~Item();
      bool isItem() override;
      bool isBlocking() override;
      virtual int getItemType() = 0;
      Item* getItem() override;
      virtual int getPoints() = 0; //treaure
      virtual void attack(double& distance, int& damage) = 0; //weapon
      virtual int getType() = 0; //weapon
      virtual int heal() = 0;//healer
      virtual int getBullets() = 0;//bullets

};

#endif   // ITEM_H_
