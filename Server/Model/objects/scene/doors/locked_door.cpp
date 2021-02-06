#include "locked_door.h"

LockedDoor::LockedDoor() {
    this->is_opened = false;
}

LockedDoor::~LockedDoor() {}

bool LockedDoor::isOpened() {
    return is_opened;
}

void LockedDoor::open() {
    this->is_opened = true;
}

bool LockedDoor::isItem() {
    return false;
}

bool LockedDoor::isBlocking() {
    if (is_opened) {
        return false;
    }
    return true;
}
