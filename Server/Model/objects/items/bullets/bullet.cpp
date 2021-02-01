#include "bullet.h"

Bullet::Bullet() {
    this->num_bullet = NUM_BULLETS_PICKED_UP;
}

int Bullet::getBullets() {
    return this->num_bullet;
}
