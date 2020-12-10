#include "weapon.h"

Weapon::Weapon() {
}

float Weapon::attack(int& damage) {
    return 0.0;
}

float Weapon::getRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distribution(1,10);
    return distribution(gen);
}

Weapon::~Weapon() {
}
