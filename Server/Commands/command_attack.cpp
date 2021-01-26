#include "command_attack.h"

CommandAttack::CommandAttack(ConnectionId id_caller, ConnectionId id_target) : Command(id_caller), id_target(id_target) {}

CommandAttack::~CommandAttack() {}

void CommandAttack::run(Game& game) {
    game.attack(id_caller, id_target);
}