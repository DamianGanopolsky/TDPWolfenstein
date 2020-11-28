#include "Player.h"
#include <utility>
#include <iostream>

#define ROTATION_SIZE 1.0

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

void Player::left_rotation() {
	std::cout << this->vision_angle << std::endl;
	float new_vision_angle = this->vision_angle + ROTATION_SIZE;
	this->vision_angle = new_vision_angle >= 360.0 ? new_vision_angle -360.0 : new_vision_angle;
}

void Player::right_rotation() {
	std::cout << this->vision_angle << std::endl;
	float new_vision_angle = this->vision_angle - ROTATION_SIZE;
	this->vision_angle = new_vision_angle < 0.0 ? 360.0 - new_vision_angle : new_vision_angle;
}