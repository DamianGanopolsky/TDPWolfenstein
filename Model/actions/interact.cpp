#include "./interact.h"

Interact::Interact(PlayerInfo &info): pickuper(info) {
    this->info = info;
}

bool Interact::interactWith(BlockingObject &obj) {
    return false;
}

bool Interact::interactWith(NonBlockingObject &obj) {
    return true;
}

bool Interact::interactWith(Door &door) {
    if(!door.isOpened()) {
        door.open();
    }
    return true;
}

bool Interact::interactWith(LockedDoor &door) {
    if(!door.isOpened()) {
        if (this->info.getKey() == 0) {
            return false;
        }
    }
    return true;
}

bool Interact::interactWith(SecretPassage &SecretPassage) {
    return true;
}

bool Interact::interactWith(Enemy &enemy) {
    return false;
}
