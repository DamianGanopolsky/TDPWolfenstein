#ifndef COMMAND_MOVE_DOWN_H
#define COMMAND_MOVE_DOWN_H

#include "command.h"

class CommandMoveDown : public Command {
    public:
        CommandMoveDown(ConnectionId id_caller);
        ~CommandMoveDown();
        void run(Game& game) override;
};

#endif