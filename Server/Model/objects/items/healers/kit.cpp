#include "kit.h"

Kit::Kit() {
    this->points = GameConfig.kit_points;
}

int Kit::getItemType() {
    return KIT;
}
