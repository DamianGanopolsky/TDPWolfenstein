#include "Command.h"
#include <iostream>

Command::Command(uint8_t event_to_command):opcode(1),command_opcode(event_to_command){
}

Command::Command(const Command& other) {
    this->opcode = other.opcode;
}
Command& Command::operator=(const Command& other) {
    this->opcode = other.opcode;
    return *this;
}

uint8_t Command::get_opcode(){
    return command_opcode;
}