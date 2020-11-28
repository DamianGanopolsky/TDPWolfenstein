#include "command_manager.h"

#include "./command_move.h"

CommandManager::CommandManager() {};

void CommandManager::applyCommand(int command, int** map, Player player) {
    int command_type = this->identifyCommandType(command);

    if (command_type == COMMAND_TYPE_MOVE) {
        CommandMove cmd;
        cmd.run(player, map, command);
        return;
    } else if (command_type == COMMAND_TYPE_ATACK) {
        // incomplete
    }
}

int CommandManager::identifyCommandType(int command) { 
    if(command >= COMMAND_MOVE_RANGE_START && command <= COMMAND_MOVE_RANGE_END) {
        return COMMAND_TYPE_MOVE;
    } else if (command == COMMAND_ATACK) {
        return COMMAND_TYPE_ATACK;
    }
    return -1;
}