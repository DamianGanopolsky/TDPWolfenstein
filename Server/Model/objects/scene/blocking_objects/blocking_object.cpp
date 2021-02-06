#include "blocking_object.h"

BlockingObject::BlockingObject() {}

BlockingObject::~BlockingObject() {}

bool BlockingObject::isItem() {
    return false;
}

bool BlockingObject::isBlocking() {
    return true;
}