#include "message.h"

Message::Message(MessageOpcode opcode, const char* message) {}
Message::~Message() {}
        
Message::Message(const Message& other) {}
Message& Message::operator=(const Message& other) {}

bool Message::send(const ConnectionId sender, const Socket& peer) {}