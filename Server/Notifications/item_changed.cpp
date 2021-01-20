#include "item_changed.h"

ItemChanged::ItemChanged() {}
ItemChanged::~ItemChanged() {}
        
ItemChanged::ItemChanged(const ItemChanged& other) {}
ItemChanged& ItemChanged::operator=(const ItemChanged& other) {}

bool ItemChanged::send(const ConnectionId sender, const Socket& peer) {}