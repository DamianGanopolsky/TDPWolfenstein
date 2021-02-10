#include "corpse.h"

Corpse::Corpse() {}

int Corpse::getItemType() {
    return CORPSE;
}

int Corpse::getPoints() {
    return -1;
}

void Corpse::attack(double& distance, int& damage) {}

const int Corpse::getType()  {
    return -1;
}

int Corpse::heal()  {
    return -1;
}

int Corpse::getBullets()  {
    return -1;
}
