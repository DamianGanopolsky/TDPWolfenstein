#include "command_move_up.h"

CommandMoveUp::CommandMoveUp(ConnectionId id_caller) : Command(id_caller) {}

CommandMoveUp::~CommandMoveUp() {}

void CommandMoveUp::run(Game& game) {
    game.startMovingUp(id_caller);
}