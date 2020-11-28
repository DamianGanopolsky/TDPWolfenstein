#include "gun.h"

Gun::Gun() {
    this->precision = GUN_PRECISION;
    this->probability_accuracy = GUN_ACCURACY;
    this->probabiliy_damage = GUN_DAMAGE;

    this->bullets_blast = GUN_BULLETS_BLAST;
    this->bullets_blast = GUN_PERIOD_BLAST;
}