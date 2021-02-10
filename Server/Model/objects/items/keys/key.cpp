#include "key.h"

Key::Key() {}

int Key::getItemType() {
    return KEY;
}

int Key::getPoints() {
    return -1;
}

void Key::attack(double& distance, int& damage) {}

const int Key::getType() {
    return -1;
}

int Key::heal() {
    return -1;
}

int Key::getBullets() {
    return -1;
}