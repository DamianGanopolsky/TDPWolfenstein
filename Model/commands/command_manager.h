#ifndef COMMAND_MANAGER_H_
#define COMMAND_MANAGER_H_

#include <unordered_map>

#include "./../constants/const_command.h"
#include "../player/player.h"

class CommandManager {
 public:
    CommandManager();
    void applyCommand(int command, int** map, Player player);
 private:
    int identifyCommandType(int command);
};

#endif    // COMMAND_MANAGER_H_
