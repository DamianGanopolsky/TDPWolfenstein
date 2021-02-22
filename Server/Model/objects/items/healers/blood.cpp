#include "blood.h"

#define BLOOD_POINTS 1

Blood::Blood() {
    this->points = BLOOD_POINTS;
}

int Blood::getItemType() {
    return BLOOD;
}
