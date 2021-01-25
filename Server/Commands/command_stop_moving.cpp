#include "command_stop_moving.h"

CommandStopMoving::CommandStopMoving(ConnectionId id_caller) : Command(id_caller) {}

CommandStopMoving::~CommandStopMoving() {}

void CommandStopMoving::run(Game& game) {
    game.stopMoving(id_caller);
}
