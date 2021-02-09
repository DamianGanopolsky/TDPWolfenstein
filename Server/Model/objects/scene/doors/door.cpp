#include "door.h"

Door::Door() {
    this->is_opened = false;
}

Door::~Door() {}

bool Door::isOpened() {
    return is_opened;
}

void Door::open() {
    this->is_opened = true;
}

bool Door::isItem() {
    return false;
}

bool Door::isBlocking() {
    if (is_opened) {
        return false;
    }
    return true;
}

Item* Door::getItem() {
    return nullptr;
}