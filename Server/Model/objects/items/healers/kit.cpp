#include "kit.h"

Kit::Kit() {
    //this->points=KIT_POINTS;
    this->points = GameConfig.kit_points;
}

int Kit::getItemType() {
    return KIT;
}
