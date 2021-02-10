#ifndef KEY_H_
#define KEY_H_

#include "./../item.h"

class Key: public Item {
    public:
        Key();
        int getItemType() override;
        int getPoints() override; //treaure
        void attack(double& distance, int& damage) override; //weapon
        const int getType() override; //weapon
        int heal() override;//healer
        int getBullets() override;//bullets
};

#endif    // KEY_H_
