#ifndef POSITION_H_
#define POSITION_H_

#include <utility>

class PlayerPosition {
 private:
    int x;
    int y;
    int width;
    int height;
    void setInitialPos(int inicial_x, int inicial_y);
 public:
    PlayerPosition();
    explicit PlayerPosition(int inicial_x, int inicial_y, int width, int height);
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    std::pair<int, int> getPosUp();
    std::pair<int, int> getPosLeft();
    std::pair<int, int> getPosDown();
    std::pair<int, int> getPosRight();
    int getX();
    int getY();
};

#endif    // POSITION_H_
