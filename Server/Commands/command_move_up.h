#ifndef COMMAND_MOVE_UP_H
#define COMMAND_MOVE_UP_H

#include "command.h"

class CommandMoveUp : public Command {
    public:
        CommandMoveUp(ConnectionId id_caller);
        ~CommandMoveUp();
        void run(Game& game) override;
};

#endif