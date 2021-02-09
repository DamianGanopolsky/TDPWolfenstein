#include "non_blocking_object.h"

NonBlockingObject::NonBlockingObject() {}

NonBlockingObject::~NonBlockingObject() {}

bool NonBlockingObject::isItem() {
    return false;
}

bool NonBlockingObject::isBlocking() {
    return false;
}

Item* NonBlockingObject::getItem() {
    return nullptr;
}