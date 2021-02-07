#ifndef COMMAND_STOP_SHOOTING_H
#define COMMAND_STOP_SHOOTING_H

#include "command.h"

class CommandStopShooting : public Command {
    public:
        CommandStopShooting(ConnectionId id_caller);
        ~CommandStopShooting();
        void run(Game& game) override;
};

#endif