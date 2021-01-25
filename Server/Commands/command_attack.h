#ifndef COMMAND_ATTACK_H
#define COMMAND_ATTACK_H

#include "command.h"

class CommandAttack : public Command {
    ConnectionId id_target;
    public:
        CommandAttack(ConnectionId id_caller, ConnectionId id_target);
        ~CommandAttack();
        void run(Game& game) override;
};

#endif