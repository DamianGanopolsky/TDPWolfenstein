#ifndef COMMAND_STOP_MOVING_H
#define COMMAND_STOP_MOVING_H

#include "command.h"

class CommandStopMoving : public Command {
    public:
        CommandStopMoving(ConnectionId id_caller);
        ~CommandStopMoving();
        void run(Game& game) override;
};

#endif