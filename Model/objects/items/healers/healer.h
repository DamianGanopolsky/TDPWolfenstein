#ifndef HEALER_H_
#define HEALER_H_

#include "../item.h"

class Healer: public Item {
 public:
    Healer();
    int heal();
 protected:
    int points;
};

#endif    // HEALER_H_
