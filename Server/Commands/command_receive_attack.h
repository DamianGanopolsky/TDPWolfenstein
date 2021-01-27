#ifndef COMMAND_RECEIVE_ATTACK_H
#define COMMAND_RECEIVE_ATTACK_H

#include "command.h"

class CommandReceiveAttack : public Command {
    ConnectionId id_target;
    int damage;
    public:
        CommandReceiveAttack(ConnectionId id_caller, int damage);
        ~CommandReceiveAttack();
        void run(Game& game) override;
};

#endif