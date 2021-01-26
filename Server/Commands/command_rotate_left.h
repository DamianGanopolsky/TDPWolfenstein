#ifndef COMMAND_ROTATE_LEFT_H
#define COMMAND_ROTATE_LEFT_H

#include "command.h"

class CommandRotateLeft : public Command {
    public:
        CommandRotateLeft(ConnectionId id_caller);
        ~CommandRotateLeft();
        void run(Game& game) override;
};

#endif