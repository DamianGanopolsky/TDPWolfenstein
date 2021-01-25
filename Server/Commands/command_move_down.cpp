#include "command_move_down.h"

CommandMoveDown::CommandMoveDown(ConnectionId id_caller) : Command(id_caller) {}

CommandMoveDown::~CommandMoveDown() {}

void CommandMoveDown::run(Game& game) {
    game.startMovingDown(id_caller);
}