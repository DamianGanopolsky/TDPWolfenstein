#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "notification.h"
#include "../Common/protocol.h"

class Message : public Notification {
    MessageOpcode opcode;
    std::string message;
    
    public:
        Message(MessageOpcode opcode, std::string message);
        virtual ~Message();
        
        Message(const Message& other);
        Message& operator=(const Message& other);

        virtual bool send(const ConnectionId sender, const Socket& peer);
};

#endif
