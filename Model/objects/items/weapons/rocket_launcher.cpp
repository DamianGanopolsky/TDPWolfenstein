#include "rocket_launcher.h"

RocketLauncher::RocketLauncher(){
    this->bullets_blast = ROCKET_LAUNCHER_BULLETS_BLAST;
    this->period_blast = ROCKET_LAUNCHER_PERIOD_BLAST;
}

float RocketLauncher::attack(int& damage) {
    //segun la distancia y el angulo establezco una proba de precision
    float rd_num = getRandomNumber();
    if (rd_num < precision) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

int RocketLauncher::getType() {
    return ROCKET_LAUNCHER_TYPE;
}