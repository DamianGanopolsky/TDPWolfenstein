#include "knife.h"
#include <iostream>

Knife::Knife() {}

Knife::~Knife() {}

void Knife::attack(double& distance, int& damage) {
    //segun si esta en el rango de ataque establezco un danio
    if (distance < 60) {
        damage=GameConfig.knife_base_damage;
    }

    //damage = 5;
    //damage=GameConfig.knife_base_damage;
}

const int Knife::getType() {
    std::cout<<"Knife: gett_type"<< std::endl;
    return KNIFE_TYPE;
}

bool Knife::inRange() {
    /*establezco si el oponente esta en el radio del jugador*/
    return true;
}