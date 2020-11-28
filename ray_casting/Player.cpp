#include "Player.h"
#include <utility>

Player::Player(int pos_x, int pos_y, float angle) :
				pos_x(pos_x), pos_y(pos_y), vision_angle(angle) {
}

Player::~Player() {
}

float Player::get_angle() const {
	return this->vision_angle;
}

int Player::get_pos_x() const {
	return this->pos_x;
}

int Player::get_pos_y() const {
	return this->pos_y;	
}