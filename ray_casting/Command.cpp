#include "Command.h"
#include <iostream>

Command::Command(uint8_t event_to_command){
    opcode=event_to_command;
    std::cout << "Event to command es" << unsigned(event_to_command) << std::endl;
    std::cout << "OPcode aca es" << opcode << std::endl;
}

Command::Command(const Command& other) {
    this->opcode = other.opcode;
}
Command& Command::operator=(const Command& other) {
    this->opcode = other.opcode;
    return *this;
}

uint8_t Command::get_opcode(){
    return opcode;
}