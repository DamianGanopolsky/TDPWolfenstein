#include "food.h"

Food::Food() {
    //this->points = FOOD_POINTS;
    this->points=GameConfig.food_points;
}

int Food::getItemType() {
    return FOOD;
}