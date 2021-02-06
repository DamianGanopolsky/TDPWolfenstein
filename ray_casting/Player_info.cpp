#include "Player_info.h"
#include <iostream>

Player_info::Player_info(int life,int resurrected,int score,int bullets):health(life),\
	lives(resurrected),scores(score),ammo(bullets),weapon(0){
}

Player_info::~Player_info(){
}

int Player_info::get_lives() const {
	return this->lives;
}

int Player_info::get_scores() const {
	return this->scores;
}

void Player_info::set_initial_status(int health,int lives,int score,int ammo){
	//lives = 8;
	//std::cout << "Seteo health a " << health << std::endl;
	scores = score;
	health = health;
	ammo = ammo;

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

void Player_info::change_weapon_status() {
	if (this->weapon_status != 0) {
		this->weapon_status--;
	}
}
