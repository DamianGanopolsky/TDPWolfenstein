#include "command_move_right.h"

CommandMoveRight::CommandMoveRight(ConnectionId id_caller) : Command(id_caller) {}

CommandMoveRight::~CommandMoveRight() {}

void CommandMoveRight::run(Game& game) {
    game.startMovingRight(id_caller);
}