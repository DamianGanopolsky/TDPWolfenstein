#include "message.h"

Message::Message() {}
Message::~Message() {}
        
Message::Message(const Message& other) {}
Message& Message::operator=(const Message& other) {}

bool Message::send(const ConnectionId sender, const Socket& peer) {}