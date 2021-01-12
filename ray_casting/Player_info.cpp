#include "Player_info.h"

Player_info::Player_info(){
}

Player_info::~Player_info(){
}

int Player_info::get_lives() const {
	return this->lives;
}

int Player_info::get_scores() const {
	return this->scores;
}

int Player_info::get_health() const {
	return this->health;
}

int Player_info::get_ammo() const {
	return this->ammo;
}

int Player_info::get_weapon() const {
	return this->weapon;
}
