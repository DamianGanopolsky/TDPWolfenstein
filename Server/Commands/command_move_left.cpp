#include "command_move_left.h"

CommandMoveLeft::CommandMoveLeft(ConnectionId id_caller) : Command(id_caller) {}

CommandMoveLeft::~CommandMoveLeft() {}

void CommandMoveLeft::run(Game& game) {
    game.startMovingLeft(id_caller);
}