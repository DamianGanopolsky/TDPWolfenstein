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

int Player_info::get_level() const{
	return this->level;
}

int Player_info::get_ammo() const {
	return this->ammo;
}

int Player_info::get_weapon() const {
	return this->weapon;
}

int Player_info::get_weapon_status() const {
	return this->weapon_status;
}

void Player_info::change_weapon(int weapon_changed){
	this->weapon=weapon_changed;
}

void Player_info::change_weapon_status() {
	if (this->weapon_status != 0) {
		this->weapon_status--;
	}
}
