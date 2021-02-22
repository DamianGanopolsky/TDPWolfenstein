#include "rocket_launcher.h"

#define ROCKET_LAUNCHER_TYPE 5

RocketLauncher::RocketLauncher(){}

RocketLauncher::~RocketLauncher() {}

void RocketLauncher::attack(double& distance, int& damage) {
    /*//segun la distancia y el angulo establezco una proba de precision
    float rd_num = getRandomNumber();
    int precision = 0 ;
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }
    damage = 0;*/
}

const int RocketLauncher::getType() {
    return ROCKET_LAUNCHER_TYPE;
}