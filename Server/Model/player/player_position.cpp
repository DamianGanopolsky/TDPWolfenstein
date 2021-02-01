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
    default:
        throw Exception("Unknown next position");
        break;
    }
    return std::pair<int, int> (-1, -1);
}

/*std::pair<int, int> PlayerPosition::getPosUp() {
    //int new_y = (this->y - 1 < 0) ? 0 : (this->y - 1);
    int new_x = (this->x + (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0)));
	int new_y = (this->y - (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0)));
    return std::pair<int, int> (new_x, new_y);
}

std::pair<int, int> PlayerPosition::getPosLeft() {
    //int new_x = (this->x - 1 < 0) ? 0 : (this->x - 1);
    int new_x = (this->x - (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0)));
	int new_y = (this->y - (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0)));
    return std::pair<int, int> (new_x, new_y);
}

std::pair<int, int> PlayerPosition::getPosDown() {
    //int new_y = (this->y + 1 > this->height) ? this->height : (this->y + 1);
    int new_x = (this->x - (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0)));
	int new_y = (this->y + (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0)));
    return std::pair<int, int> (new_x, new_y);
}

std::pair<int, int> PlayerPosition::getPosRight() {
    //int new_x = (this->x + 1 < this->width) ? (this->x + 1) : this->width;
    int new_x = (this->x + (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0)));
	int new_y = (this->y + (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0)));
    return std::pair<int, int> (new_x, new_y);
}*/

void PlayerPosition::moveUp() {
    //this->y = (this->y - 1 < 0) ? 0 : (this->y - 1);
    this->x += (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0));
	this->y -= (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0));
}

void PlayerPosition::moveLeft() {
    //this->x = (this->x - 1 < 0) ? 0 : (this->x - 1);
    this->x -= (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0));
	this->y -= (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0));	
}

void PlayerPosition::moveDown() {
    //this->y = (this->y + 1 > this->height) ? this->height : (this->y + 1);
    this->x -= (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0));
	this->y += (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0));
}

void PlayerPosition::moveRight() {
    //this->x = (this->x + 1 < this->width) ? (this->x + 1) : this->width;
    this->x += (int) (DISPLACEMENT * sin(this->vision_angle * PI / 180.0));
	this->y += (int) (DISPLACEMENT * cos(this->vision_angle * PI / 180.0));	
}

void PlayerPosition::rotateLeft() {
	float new_vision_angle = this->vision_angle + ROTATION_SIZE;
	this->vision_angle = new_vision_angle >= 360.0 ? new_vision_angle - 360.0 : new_vision_angle;
}

void PlayerPosition::rotateRight() {
	float new_vision_angle = this->vision_angle - ROTATION_SIZE;
	this->vision_angle = new_vision_angle < 0.0 ? 360.0 + new_vision_angle : new_vision_angle;
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