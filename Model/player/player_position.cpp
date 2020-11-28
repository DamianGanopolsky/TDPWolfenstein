#include "player_position.h"

PlayerPosition::PlayerPosition(){}

void PlayerPosition::setInitialPos(int inicial_x, int inicial_y) {
    if (inicial_x < 0 || inicial_x > this->width ) {
        this->x = 0;
    } else {
        this->x = inicial_x;
    }
    if (inicial_y < 0 || inicial_y > this->height ) {
        this->y = 0;
    } else {
        this->y = inicial_y;
    }
}

PlayerPosition::PlayerPosition(int inicial_x, int inicial_y, int width, int height) {
    this->width = width;
    this->height = height;
    this->setInitialPos(inicial_x, inicial_y);
}

std::pair<int, int> PlayerPosition::getPosUp() {
    int new_y = (this->y - 1 < 0) ? 0 : (this->y - 1);
    return std::pair<int, int> (this->x, new_y);
}

std::pair<int, int> PlayerPosition::getPosLeft() {
    int new_x = (this->x - 1 < 0) ? 0 : (this->x - 1);
    return std::pair<int, int> (new_x, this->y);
}

std::pair<int, int> PlayerPosition::getPosDown() {
    int new_y = (this->y + 1 > this->height) ? this->height : (this->y + 1);
    return std::pair<int, int> (this->x, new_y);
}

std::pair<int, int> PlayerPosition::getPosRight() {
    int new_x = (this->x + 1 < this->width) ? (this->x + 1) : this->width;
    return std::pair<int, int> (new_x, this->y);
}

void PlayerPosition::moveUp() {
    this->y = (this->y - 1 < 0) ? 0 : (this->y - 1);
}

void PlayerPosition::moveLeft() {
    this->x = (this->x - 1 < 0) ? 0 : (this->x - 1);
}

void PlayerPosition::moveDown() {
    this->y = (this->y + 1 > this->height) ? this->height : (this->y + 1);
}

void PlayerPosition::moveRight() {
    this->x = (this->x + 1 < this->width) ? (this->x + 1) : this->width;
}

int PlayerPosition::getX() {
    return this->x;
}
int PlayerPosition::getY() {
    return this->y;
}