#include "healer.h"

Healer::Healer() {
    this->points = 0;
}

// Recieves current life value of character
// Returns new life value of character 
int Healer::heal() {
    return this->points;
}
