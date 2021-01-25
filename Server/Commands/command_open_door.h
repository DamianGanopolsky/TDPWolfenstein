#ifndef COMMAND_OPEN_DOOR_H
#define COMMAND_OPEN_DOOR_H

#include "command.h"

class CommandOpenDoor : public Command {
    public:
        CommandOpenDoor(ConnectionId id_caller);
        ~CommandOpenDoor();
        void run(Game& game) override;
};

#endif