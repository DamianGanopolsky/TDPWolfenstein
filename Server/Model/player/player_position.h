#ifndef POSITION_H_
#define POSITION_H_

#include <utility>
#include <cmath>
#include "../constants/config_player.h"
#include "../constants/YamlConfig.h"
#include "../../../Common/exception.h"

class PlayerPosition {
 private:
    int x;
    int y;
    float vision_angle;
    Direction direction;
    Rotation rotation;
    int width;
    int height;
 public:
    PlayerPosition(int width, int height);
    explicit PlayerPosition(int inicial_x, int inicial_y, int width, int height);
    ~PlayerPosition();
    void setPosition(int inicial_x, int inicial_y);
    void move(Direction direction);
    void rotate(Rotation rotation);
    /*void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void rotateLeft();
    void rotateRight();*/
    std::pair<int, int> getNextPos(Direction direction);
    void changeDirection(Direction direction);
    void changeRotation(Rotation rotation);
    Direction getDirection();
    Rotation getRotation();
    int getX();
    int getY();
    float getAngle();
};

#endif    // POSITION_H_