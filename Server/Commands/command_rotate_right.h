#ifndef COMMAND_ROTATE_RIGHT_H
#define COMMAND_ROTATE_RIGHT_H

#include "command.h"

class CommandRotateRight : public Command {
    public:
        CommandRotateRight(ConnectionId id_caller);
        ~CommandRotateRight();
        void run(Game& game) override;
};

#endif
