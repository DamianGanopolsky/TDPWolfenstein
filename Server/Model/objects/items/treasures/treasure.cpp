#include "treasure.h"

int Treasure::getPoints() {
    return this->points;
}

int Treasure::getItemType() {
    return TREASURE;
}

void Treasure::attack(double& distance, int& damage) {}

const int Treasure::getType() {
    return -1;
}

int Treasure::heal() {
    return -1;
}

int Treasure::getBullets() {
    return -1;
}