#include "food.h"

Food::Food() {
    this->points = FOOD_POINTS;
}

int Food::getItemType() {
    return FOOD;
}