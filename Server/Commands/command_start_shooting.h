#ifndef COMMAND_START_SHOOTING_H
#define COMMAND_START_SHOOTING_H

#include "command.h"

class CommandStartShooting : public Command {
    public:
        CommandStartShooting(ConnectionId id_caller);
        ~CommandStartShooting();
        void run(Game& game) override;
};

#endif