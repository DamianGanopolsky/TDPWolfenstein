#include "command_rotate_right.h"

CommandRotateRight::CommandRotateRight(ConnectionId id_caller) : Command(id_caller) {}

CommandRotateRight::~CommandRotateRight() {}

void CommandRotateRight::run(Game& game) {
    game.startRotatingRight(id_caller);
}
