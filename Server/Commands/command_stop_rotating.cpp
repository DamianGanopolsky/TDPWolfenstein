#include "command_stop_rotating.h"

CommandStopRotating::CommandStopRotating(ConnectionId id_caller) : Command(id_caller) {}

CommandStopRotating::~CommandStopRotating() {}

void CommandStopRotating::run(Game& game) {
    game.stopRotating(id_caller);
}
