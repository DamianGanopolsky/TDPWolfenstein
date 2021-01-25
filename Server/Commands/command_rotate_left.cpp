#include "command_rotate_left.h"

CommandRotateLeft::CommandRotateLeft(ConnectionId id_caller) : Command(id_caller) {}

CommandRotateLeft::~CommandRotateLeft() {}

void CommandRotateLeft::run(Game& game) {
    game.startRotatingLeft(id_caller);
}