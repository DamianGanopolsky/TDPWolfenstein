#include "door.h"

Door::Door() {
    this->is_opened = false;
}
bool Door::isOpened() {
    return is_opened;
}

void Door::open() {
    this->is_opened = true;
}
    
Door::~Door() {
}
