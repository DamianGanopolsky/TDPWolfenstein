#ifndef COMMAND_MOVE_RIGHT_H
#define COMMAND_MOVE_RIGHT_H

#include "command.h"

class CommandMoveRight : public Command {
    public:
        CommandMoveRight(ConnectionId id_caller);
        ~CommandMoveRight();
        void run(Game& game) override;
};

#endif