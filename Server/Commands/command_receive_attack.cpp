#include "command_receive_attack.h"

CommandReceiveAttack::CommandReceiveAttack(ConnectionId id_caller, int damage) : Command(id_caller), damage(damage) {}

CommandReceiveAttack::~CommandReceiveAttack() {}

void CommandReceiveAttack::run(Game& game) {
    game.receiveAttack(id_caller, damage);
}