#include "knife.h"
#include <iostream>

Knife::Knife() {}

void Knife::attack(double& distance, int& damage) {
    //segun si esta en el rango de ataque establezco un danio
    if (inRange()) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

const int Knife::getType() {
    std::cout<<"Knife: gett_type"<< std::endl;
    return KNIFE_TYPE;
}

bool Knife::inRange() {
    /*establezco si el oponente esta en el radio del jugador*/
    return true;
}