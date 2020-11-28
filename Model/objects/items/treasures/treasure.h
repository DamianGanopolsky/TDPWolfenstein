#ifndef TREASURE_H
#define TREASURE_H

#include "./../item.h"

class Treasure: public Item  {
 public:
    int getPoints();
 protected:
    int points;
};

#endif    // TREASURE_H
