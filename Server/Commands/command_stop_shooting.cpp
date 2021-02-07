#include "command_stop_shooting.h"

CommandStopShooting::CommandStopShooting(ConnectionId id_caller) : Command(id_caller) {}

CommandStopShooting::~CommandStopShooting() {}

void CommandStopShooting::run(Game& game) {
    game.stopShooting(id_caller);
}