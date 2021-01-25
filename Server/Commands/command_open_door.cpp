#include "command_open_door.h"

CommandOpenDoor::CommandOpenDoor(ConnectionId id_caller) : Command(id_caller) {}

CommandOpenDoor::~CommandOpenDoor() {}

void CommandOpenDoor::run(Game& game) {
    game.openDoor(id_caller);
}