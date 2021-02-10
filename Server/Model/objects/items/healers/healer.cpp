#include "healer.h"

Healer::Healer() {
    this->points = 0;
}

// Recieves current life value of character
// Returns new life value of character 
int Healer::heal() {
    return this->points;
}

int Healer::getPoints() {
    return -1;
}

void Healer::attack(double& distance, int& damage) {}

const int Healer::getType() {
    return -1;
}

int Healer::getBullets() {
    return -1;
}