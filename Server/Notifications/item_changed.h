#ifndef ITEM_CHANGED_H
#define ITEM_CHANGED_H

#include "notification.h"

class ItemChanged : public Notification {
    public:
        ItemChanged();
        virtual ~ItemChanged();
        
        ItemChanged(const ItemChanged& other);
        ItemChanged& operator=(const ItemChanged& other);

        virtual bool send(const ConnectionId sender, const Socket& peer);
};

#endif