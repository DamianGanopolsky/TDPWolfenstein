#include "player_position.h"

PlayerPosition::PlayerPosition(int width, int height){
    this->width = width;
    this->height = height;
    //generar valores random
    this->_setInitialPos(100, 100);
    //cambiar el angulo segun lo que llega??
    this->vision_angle = 270;
    this->direction = UP_DIR; //default
    this->rotation = RIGHT_ROTATION_DIR; //default
}

PlayerPosition::PlayerPosition(int inicial_x, int inicial_y, int width, int height) {
    this->width = width;
    this->height = height;
    this->_setInitialPos(inicial_x, inicial_y);
    //cambiar el angulo segun lo que llega??
    this->vision_angle = 270;
    this->direction = UP_DIR; //default
    this->rotation = RIGHT_ROTATION_DIR; //default
}

PlayerPosition::~PlayerPosition() {}

void PlayerPosition::_setInitialPos(int inicial_x, int inicial_y) {
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

std::pair<int, int> PlayerPosition::getNextPos(Direction direction) {
    switch (direction) {
        case UP_DIR: {
            int new_x = (this->x + (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0)));
            int new_y = (this->y - (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0)));
            return std::pair<int, int> (new_x, new_y);
        }
        case DOWN_DIR: {
            int new_x = (this->x - (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0)));
            int new_y = (this->y + (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0)));
            return std::pair<int, int> (new_x, new_y);
        }
        case LEFT_DIR: {
            int new_x = (this->x - (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0)));
            int new_y = (this->y - (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0)));
            return std::pair<int, int> (new_x, new_y);
        }
        case RIGHT_DIR: {
            int new_x = (this->x + (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0)));
            int new_y = (this->y + (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0)));
            return std::pair<int, int> (new_x, new_y);
        }
        default: {
            throw Exception("Unknown next position");
            break;
        }
    }
    return std::pair<int, int> (-1, -1);
}

void PlayerPosition::move(Direction direction) {
    std::cout <<"PlayerPosition: move()"<< std::endl;
    std::cout <<"PlayerPosition: direction"<< (unsigned)direction <<std::endl;
    switch (direction) {
        case UP_DIR: {
            std::cout <<"PlayerPosition: moveUp"<< std::endl;
            this->x += (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0));
	        this->y -= (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0));
            break;
        }
        case DOWN_DIR: {
            std::cout <<"PlayerPosition: moveDown"<< std::endl;
            this->x -= (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0));
	        this->y += (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0));
            break;
        }
        case LEFT_DIR: {
            std::cout <<"PlayerPosition: moveLeft"<< std::endl;
            this->x -= (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0));
	        this->y -= (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0));
            break;	
        }
        case RIGHT_DIR: {
            std::cout <<"PlayerPosition: moveRight"<< std::endl;
            this->x += (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0));
	        this->y += (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0));
            break;
        }
        default: {
            throw Exception("Unknown position");
            break;
        }
    }
}

void PlayerPosition::rotate(Rotation rotation) {
    switch (rotation) {
        case LEFT_ROTATION_DIR: {
            float new_vision_angle = this->vision_angle + ROTATION_SIZE;
	        this->vision_angle = new_vision_angle >= 360.0 ? new_vision_angle - 360.0 : new_vision_angle;
            break;
        }
        case RIGHT_ROTATION_DIR: {
            float new_vision_angle = this->vision_angle - ROTATION_SIZE;
	        this->vision_angle = new_vision_angle < 0.0 ? 360.0 + new_vision_angle : new_vision_angle;
            break;
        }
        default: {
            throw Exception("Unknown rotation");
            break;
        }
    }
}

void PlayerPosition::changeDirection(Direction direction) {
    this->direction = direction;
}

void PlayerPosition::changeRotation(Rotation rotation) {
    this->rotation = rotation;
}

Direction PlayerPosition::getDirection() {
    return this->direction;
}

Rotation PlayerPosition::getRotation() {
    return this->rotation;
}

int PlayerPosition::getX() {
    return this->x;
}

int PlayerPosition::getY() {
    return this->y;
}

float PlayerPosition::getAngle() {
	return this->vision_angle;
}
