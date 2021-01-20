#ifndef EVENT_H
#define EVENT_H

#include "notification.h"

class Event : public Notification {
    public:
        Event();
        virtual ~Event();
        
        Event(const Event& other);
        Event& operator=(const Event& other);

        virtual bool send(const ConnectionId sender, const Socket& peer);
};

#endif