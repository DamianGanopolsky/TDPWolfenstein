#include "position.h"

Position::Position(){}

Position::Position(int inicial_x, int inicial_y, int width, int height) {
    this->x = inicial_x;
    this->y = inicial_y;
    this->width = width;
    this->height = height;
}


std::pair<int, int> Position::getPosUp() {
    int new_y = (y - 1 < 0) ? 0 : (y - 1);
    return std::pair<int, int> (this->x, new_y);
}

std::pair<int, int> Position::getPosLeft() {
    int new_x = (this->x + 1 < this->width) ? (this->x + 1) : this->width;
    return std::pair<int, int> (new_x, this->y);
}

std::pair<int, int> Position::getPosDown() {
    int new_y = (y + 1 < this->height) ? (y + 1) : this->height;
    return std::pair<int, int> (this->x, new_y);
}

std::pair<int, int> Position::getPosRight() {
    int new_x = (x - 1 < 0) ? 0 : (x - 1);
    return std::pair<int, int> (new_x, this->y);
}

void Position::moveUp() {
    this->y = (this->y - 1 < 0) ? 0 : (this->y - 1);
}

void Position::moveLeft() {
    this->x = (this->x - 1 < 0) ? 0 : (this->x - 1);
}

void Position::moveDown() {
    this->y = (this->y + 1 < this->height) ? (this->y + 1) : this->height;
}

void Position::moveRight() {
    this->x = (this->x + 1 < this->width) ? (this->x + 1) : this->width;
}

int Position::getX() {
    return this->x;
}

int Position::getY() {
    return this->y;
}
