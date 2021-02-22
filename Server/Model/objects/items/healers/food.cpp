#include "food.h"

Food::Food() {
    this->points=GameConfig.food_points;
}

int Food::getItemType() {
    return FOOD;
}