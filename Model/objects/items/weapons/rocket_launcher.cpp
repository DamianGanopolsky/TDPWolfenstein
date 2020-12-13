#include "rocket_launcher.h"

RocketLauncher::RocketLauncher(){
    this->precision = ROCKET_LAUNCHER_PRECISION;
    this->probability_accuracy = ROCKET_LAUNCHER_ACCURACY;
    this->probabiliy_damage = ROCKET_LAUNCHER_DAMAGE;

    this->bullets_blast = ROCKET_LAUNCHER_BULLETS_BLAST;
    this->bullets_blast = ROCKET_LAUNCHER_PERIOD_BLAST;
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