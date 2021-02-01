#include "message.h"

Message::Message(MessageOpcode opcode, std::string message) : 
                opcode(opcode), message(message) {}
Message::~Message() {}
        
Message::Message(const Message& other) {
    this->opcode = other.opcode;
    this->message = other.message;
}
Message& Message::operator=(const Message& other) {
    this->opcode = other.opcode;
    this->message = other.message;
    return *this;
}

bool Message::send(const ConnectionId sender, const Socket& peer) {
    return true;
}