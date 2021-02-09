#include "item.h"

Item::Item() {}

Item::~Item() {}

bool Item::isItem() {
    return true;
}

bool Item::isBlocking() {
    return false;
}

Item* Item::getItem() {
    return this;
}