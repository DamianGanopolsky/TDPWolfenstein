#include "./command_move.h"
#include "./../constants/const_object_map.h"
#include "./../constants/const_command.h"
#include <cmath>

CommandMove::CommandMove() {}

void CommandMove::run(Player &player, int **map, int command) {
    PlayerPosition pos = player.getPos();
    std::pair<int, int> next_pos = this->getNextPos(pos, command);
    bool changeCell = this->changeCell(pos, next_pos);
    if (changeCell || (next_pos.first == -1 && next_pos.second == -1)) {
        int object_code = map[next_pos.first][next_pos.second];
        Object obj = objMap.getObject(object_code);
        
        bool not_blocking = interactor.interactWith(player, map, obj);
        if (not_blocking) {
            this->move(pos, command);
        }
    } else { //se mueve dentro de la misma celda
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

bool CommandMove::changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos) {
    int current_x = pos.getX();
    int current_y = pos.getY();
    int next_x = next_pos.first;
    int next_y = next_pos.second;
    float value_x = abs((current_x/POINTS_PER_CELL)-(next_x/POINTS_PER_CELL));
    float value_y = abs((current_y/POINTS_PER_CELL)-(next_y/POINTS_PER_CELL));
    if (value_x >= 1 || value_y >= 1) {
        return true;
    }
    return false;
}