#include "bullet.h"

Bullet::Bullet() {
    //this->num_bullet = NUM_BULLETS_PICKED_UP;
    this->num_bullet=GameConfig.num_bullets_picked_up;
}

int Bullet::getBullets() {
    return this->num_bullet;
}

int Bullet::getItemType() {
    return BULLETS;
}

int Bullet::getPoints() {
    return -1;
}

void Bullet::attack(double& distance, int& damage) {}

const int Bullet::getType()  {
    return -1;
}

int Bullet::heal()  {
    return -1;
}