#ifndef CORPSE_H_
#define CORPSE_H_

#include "./../item.h"

class Corpse: public Item {
    public:
        Corpse();
        int getItemType() override;
        int getPoints() override; //treaure
        void attack(double& distance, int& damage) override; //weapon
        int getType() override; //weapon
        int heal() override;//healer
        int getBullets() override;//bullets
};

#endif    // CORPSE_H_
