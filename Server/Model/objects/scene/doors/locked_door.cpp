#include "locked_door.h"

LockedDoor::LockedDoor() {
    this->is_opened = false;
}
bool LockedDoor::isOpened() {
    return is_opened;
}

void LockedDoor::open() {
    this->is_opened = true;
}
    
LockedDoor::~LockedDoor() {
}
