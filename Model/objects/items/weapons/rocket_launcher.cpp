#include "rocket_launcher.h"

RocketLauncher::RocketLauncher(){
    this->precision = ROCKET_LAUNCHER_PRECISION;
    this->probability_accuracy = ROCKET_LAUNCHER_ACCURACY;
    this->probabiliy_damage = ROCKET_LAUNCHER_DAMAGE;

    this->bullets_blast = ROCKET_LAUNCHER_BULLETS_BLAST;
    this->bullets_blast = ROCKET_LAUNCHER_PERIOD_BLAST;
}