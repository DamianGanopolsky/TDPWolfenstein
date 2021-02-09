#include "weapon.h"

Weapon::Weapon() {}

Weapon::~Weapon() {}

float Weapon::getRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distribution(1,10);
    return distribution(gen);
}

int Weapon::getItemType() {
    return WEAPON;
}

int Weapon::getPoints() {
    return -1;
}

int Weapon::heal() {
    return -1;
}

int Weapon::getBullets() {
    return -1;
}