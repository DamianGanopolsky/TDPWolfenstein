#include "blood.h"

Blood::Blood() {
    this->points = BLOOD_POINTS;
}

int Blood::getItemType() {
    return BLOOD;
}
