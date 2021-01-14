#include "knife.h"

Knife::Knife() {}

float Knife::attack(int& damage) {
    //segun si esta en el rango de ataque establezco un danio
    if (inRange()) {
        damage = (int) getRandomNumber();
    }
    damage = 0;
}

int Knife::getType() {
    return KNIFE_TYPE;
}