#ifndef COMMAND_MOVE_LEFT_H
#define COMMAND_MOVE_LEFT_H

#include "command.h"

class CommandMoveLeft : public Command {
    public:
        CommandMoveLeft(ConnectionId id_caller);
        ~CommandMoveLeft();
        void run(Game& game) override;
};

#endif