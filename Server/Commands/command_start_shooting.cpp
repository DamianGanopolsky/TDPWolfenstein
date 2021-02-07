#include "command_start_shooting.h"

CommandStartShooting::CommandStartShooting(ConnectionId id_caller) : Command(id_caller) {}

CommandStartShooting::~CommandStartShooting() {}

void CommandStartShooting::run(Game& game) {
    game.startShooting(id_caller);
}