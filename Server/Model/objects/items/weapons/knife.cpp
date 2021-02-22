#include "knife.h"
#include <iostream>

Knife::Knife() {}

Knife::~Knife() {}

bool Knife::_inRange() {
    /*establezco si el oponente esta en el radio del jugador*/
    return true;
}

void Knife::attack(double& distance, int& damage) {
    if (distance < GameConfig.knife_max_range) {
        damage=GameConfig.knife_base_damage;
    }
}

const int Knife::getType() {
    return KNIFE_TYPE;
}
