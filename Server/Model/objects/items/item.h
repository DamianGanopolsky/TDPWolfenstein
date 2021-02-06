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
};

#endif   // ITEM_H_
