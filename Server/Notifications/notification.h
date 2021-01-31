#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <cstdint>
#include <string>
#include "../../Common/socket.h"
#include "../../Common/defs.h"

class Notification {
   public:
    Notification();
    virtual ~Notification();

    Notification(const Notification&) = delete;
    Notification& operator=(const Notification&) = delete;
    Notification(Notification&& other) = delete;
    Notification& operator=(Notification&&) = delete;

    virtual bool send(const ConnectionId sender, const Socket& peer) = 0;
};

#endif
