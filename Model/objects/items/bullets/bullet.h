#ifndef BULLET_H_
#define BULLET_H_

#include "./../item.h"

class Bullet: public Item {
 public:
    Bullet();
    int getBullets();
 private:
    int num_bullet;
};

#endif    // BULLET_H_
