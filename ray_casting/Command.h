#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <stdint.h>

class Command {
public:
    Command(uint8_t event_to_command);
    Command(const Command& other);
    Command& operator=(const Command& other);

    uint8_t get_opcode();

private:
    uint8_t opcode;
};

#endif