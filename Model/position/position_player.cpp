#include "position_player.h"

Position::Position(int inicial_x, int inicial_y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}


std::pair<int, int> Position::getPosUp() {
    int new_y = (y + 1 < this->height) ? (y + 1) : this->height;
    return std::pair<int, int> (this->x, new_y);
}

std::pair<int, int> Position::getPosLeft() {
    int new_x = (x - 1 < 0) ? 0 : (x - 1);
    return std::pair<int, int> (new_x, this->y);
}

std::pair<int, int> Position::getPosDown() {
    int new_y = (y - 1 < 0) ? 0 : (y - 1);
    return std::pair<int, int> (this->x, new_y);
}

std::pair<int, int> Position::getPosRight() {
    int new_x = (x + 1 < this->width) ? (x + 1) : this->width;
    return std::pair<int, int> (new_x, this->y);
}

void Position::moveUp() {
    y = (y + 1 < this->height) ? (y + 1) : this->height;
}

void Position::moveLeft() {
    x = (x - 1 < 0) ? 0 : (x - 1);
}

void Position::moveDown() {
    y = (y - 1 < 0) ? 0 : (y - 1);
}

void Position::moveRight() {
    x = (x + 1 < this->width) ? (x + 1) : this->width;
}
