#include "gun.h"

Gun::Gun() {
    this->bullets_blast = GUN_BULLETS_BLAST;
    this->period_blast = GUN_PERIOD_BLAST;
}

Gun::~Gun() {}

void Gun::attack(double& distance, int& damage) {
    /*float rd_num = getRandomNumber();
    int precision = 0 ;
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }*/
    //damage = 5;
    if(distance<70){
        damage = GameConfig.gun_base_damage;
    }
    else{
        damage = GameConfig.gun_base_damage/2;
    }
}

const int Gun::getType() {
    return GUN_TYPE;
}