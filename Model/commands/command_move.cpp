#include "./command_move.h"
#include "./../constants/const_object_map.h"
#include "./../constants/const_command.h"

CommandMove::CommandMove() {}

void CommandMove::run(Player &player, int **map, int command) {
    PlayerPosition pos = player.getPos();

    this->move(pos, command);
    std::pair<int, int> next_pos = this->getNextPos(pos, command);

    int object_code = map[next_pos.first][next_pos.second];
    Object obj = objMap.getObject(object_code);
    
    bool not_blocking = interactor.interactWith(player, map, obj);
    if (not_blocking) {
        this->move(pos, command);
    }
}

void CommandMove::move(PlayerPosition &pos, int command) {
    switch (command) {
        case COMMAND_UP: pos.moveUp(); break;
        case COMMAND_DOWN: pos.moveDown(); break;
        case COMMAND_LEFT: pos.moveLeft(); break;
        case COMMAND_RIGHT: pos.moveRight(); break;
        default: break;
    }
}

std::pair<int, int> CommandMove::getNextPos(PlayerPosition &pos, int command) {
    switch (command) {
        case COMMAND_UP: return pos.getPosUp();
        case COMMAND_DOWN: return pos.getPosDown();
        case COMMAND_LEFT: return pos.getPosLeft();
        case COMMAND_RIGHT: return pos.getPosRight();
        default: return std::pair<int, int>(-1,-1);
    }
}
