#ifndef MESSAGE_H
#define MESSAGE_H

#include "notification.h"

class Message : public Notification {
    public:
        Message();
        virtual ~Message();
        
        Message(const Message& other);
        Message& operator=(const Message& other);

        virtual bool send(const ConnectionId sender, const Socket& peer);
};

#endif
