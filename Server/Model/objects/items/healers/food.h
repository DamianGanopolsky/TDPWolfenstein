#ifndef FOOD_H_
#define FOOD_H_

#include "healer.h"

class Food: public Healer {
    public:
        Food();
        int getItemType() override;
};

#endif // FOOD_H_
