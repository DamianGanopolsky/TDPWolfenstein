#include "../const.h"
#include "Player_panel_status.h"
#include <SDL2/SDL_image.h>
#include <utility>
#include <cmath>
#include <iostream>

Player_panel_status::Player_panel_status(SDL_Renderer*& renderer) :
										renderer(renderer), 
										face_status(renderer, IMAGE_FACES_PATH, TOTAL_FACES),
										weapon_status(renderer, IMAGE_WEAPONS_PATH, TOTAL_WEAPONS),
										number_status(renderer, IMAGE_NUMBERS_PATH, TOTAL_NUMBERS), 
										guardia_status(renderer, IMAGE_GUARDIAS_PATH, TOTAL_GUARDIAS),
										knife_status(renderer,IMAGE_KNIFE_PATH,TOTAL_KNIFES),
										pistola_status(renderer, IMAGE_PISTOLA_PATH, TOTAL_PISTOLAS),
										automaticgun_status(renderer,IMAGE_AUTOMATICGUN_PATH,TOTAL_AUTOMATICGUNS),
										chaincannon_status(renderer,IMAGE_CHAINCANNON_PATH,TOTAL_CHAINCANNONS),
										elite_guard_status(renderer,IMAGE_ELITE_GUARDIAS_PATH ,TOTAL_ELITE_GUARDIAS),
										official_guard_status(renderer,IMAGE_OFFICER_GUARDIAS_PATH,TOTAL_OFFICER_GUARDIAS),
										bullets(renderer,IMAGE_BULLETS_PATH,TOTAL_BULLETS),
										food(renderer,IMAGE_FOOD_PATH,TOTAL_FOOD),
										medical_kit(renderer,IMAGE_MEDICAL_KIT_PATH,TOTAL_MEDICAL_KIT),
										key(renderer,IMAGE_KEY_PATH,TOTAL_KEYS),
										automatic_gun(renderer,IMAGE_AUTOMATIC_GUN_PATH,TOTAL_AUTOMATIC_GUNS),
										treasure(renderer,IMAGE_TREASURE_PATH,TOTAL_TREASURES),
										chain_cannon(renderer,IMAGE_CHAIN_CANNON_PATH,TOTAL_CHAIN_CANNONS) {
	SDL_Surface *status_img = IMG_Load("../ray_casting/sprites/hud.png");
	this->status_tex = SDL_CreateTextureFromSurface(this->renderer, status_img);
	SDL_FreeSurface(status_img);
}

Player_panel_status::Player_panel_status(Player_panel_status&& other) :
										renderer(other.renderer), 
										face_status(std::move(other.face_status)),
										weapon_status(std::move(other.weapon_status)),
										number_status(std::move(other.number_status)),	
										guardia_status(std::move(other.guardia_status)),
										knife_status(std::move(other.knife_status)),	
										pistola_status(std::move(other.pistola_status)),
										automaticgun_status(std::move(other.automaticgun_status)),
										chaincannon_status(std::move(other.chaincannon_status)),
										elite_guard_status(std::move(other.elite_guard_status)),
										official_guard_status(std::move(other.official_guard_status)),
										bullets(std::move(other.bullets)),
										food(std::move(other.food)),
										medical_kit(std::move(other.medical_kit)),
										key(std::move(other.key)),
										automatic_gun(std::move(other.automatic_gun)),
										treasure(std::move(other.treasure)),
										chain_cannon(std::move(other.chain_cannon)) {	
	this->status_tex = other.status_tex;
	other.status_tex = nullptr;
}

Player_panel_status::Player_panel_status() : status_tex(nullptr) {	
}

Player_panel_status& Player_panel_status::operator=(Player_panel_status&& other) {
	if (this == &other) {
		return *this;
	}

	if (this->status_tex) {
		SDL_DestroyTexture(this->status_tex);
	}
	this->renderer = other.renderer;
	this->status_tex = other.status_tex;
	this->face_status = std::move(other.face_status);
	this->weapon_status = std::move(other.weapon_status);
	this->number_status = std::move(other.number_status);
	this->guardia_status = std::move(other.guardia_status);
	this->elite_guard_status=std::move(other.elite_guard_status);
	this->knife_status=std::move(other.knife_status);
	this->pistola_status = std::move(other.pistola_status);
	this->automaticgun_status=std::move(other.automaticgun_status);
	this->chaincannon_status=std::move(other.chaincannon_status);
	this->official_guard_status= std::move(other.official_guard_status);
	this->bullets=std::move(other.bullets);
	this->food=std::move(other.food);
	this->medical_kit=std::move(other.medical_kit);
	this->automatic_gun=std::move(other.automatic_gun);
	this->chain_cannon=std::move(other.chain_cannon);
	this->treasure=std::move(other.treasure);
	this->key=std::move(other.key);
	other.status_tex = nullptr;
	return *this;	
}

Player_panel_status::~Player_panel_status() {
	if (this->status_tex) {
		SDL_DestroyTexture(this->status_tex);
	}
}

void Player_panel_status::copy_to_rederer(Player_info& player_info) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH;
	SrcR.h = PANEL_HEIGHT * 0.2;
	SrcR.x = 0;
	SrcR.y = PANEL_HEIGHT - SrcR.h;
    SDL_RenderCopy(this->renderer, this->status_tex, NULL, &SrcR);
    
	this->copy_to_rederer_weapon(player_info);
	this->copy_to_rederer_face(player_info.get_health());
	this->copy_to_rederer_lives(player_info.get_lives());
	this->copy_to_rederer_health(player_info.get_health());
	this->copy_to_rederer_ammo(player_info.get_ammo());
	this->copy_to_rederer_score(player_info.get_scores());
	this->copy_to_rederer_level(player_info.get_level());
}

void Player_panel_status::copy_to_rederer_weapon(Player_info& info) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.2;
	SrcR.h = PANEL_HEIGHT * 0.19;
	SrcR.x = PANEL_WIDTH * 0.795;
	SrcR.y = PANEL_HEIGHT - SrcR.h;

	this->weapon_status.copy_to_rederer(info.get_weapon(), &SrcR);

	SrcR.w = PANEL_WIDTH * 0.25;
	SrcR.h = PANEL_HEIGHT * 0.25;
	SrcR.x = (PANEL_WIDTH - SrcR.w) / 2 ;
	SrcR.y = PANEL_HEIGHT * 0.8 - SrcR.h;

	switch(info.get_weapon()){
		case 0:
			this->knife_status.copy_to_rederer(info.get_weapon_status(),&SrcR);
			break;
		case 1:
			this->pistola_status.copy_to_rederer(info.get_weapon_status(), &SrcR);
			break;
		case 2:
			this->automaticgun_status.copy_to_rederer(info.get_weapon_status(),&SrcR);
			break;
		case 3:
			this->chaincannon_status.copy_to_rederer(info.get_weapon_status(),&SrcR);
			break;
	}
	info.change_weapon_status();
}

void Player_panel_status::copy_to_rederer_face(int health) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.1;
	SrcR.h = PANEL_HEIGHT * 0.19;
	SrcR.x = PANEL_WIDTH * 0.415;
	SrcR.y = PANEL_HEIGHT - SrcR.h;

	int face_number = ((MAX_HEALTH - health) / (MAX_HEALTH / (TOTAL_FACES - 1)));

	this->face_status.copy_to_rederer(face_number, &SrcR);
}

void Player_panel_status::copy_to_rederer_lives(int lives) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.03;
	SrcR.h = PANEL_HEIGHT * 0.10;
	SrcR.x = PANEL_WIDTH * 0.340;
	SrcR.y = PANEL_HEIGHT - SrcR.h * 1.25;

	this->number_status.copy_to_rederer(lives, &SrcR);
}

void Player_panel_status::copy_to_rederer_health(int health) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.025;
	SrcR.h = PANEL_HEIGHT * 0.10;
	SrcR.x = PANEL_WIDTH * 0.525;
	SrcR.y = PANEL_HEIGHT - SrcR.h * 1.25;

	this->copy_to_rederer_number(health, 3, SrcR, false);
}

void Player_panel_status::copy_to_rederer_score(int score) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.025;
	SrcR.h = PANEL_HEIGHT * 0.10;
	SrcR.x = PANEL_WIDTH * 0.1719;
	SrcR.y = PANEL_HEIGHT* 0.87;

	this->copy_to_rederer_number(score, 1, SrcR, true);
}

void Player_panel_status::copy_to_rederer_level(int level) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.025;
	SrcR.h = PANEL_HEIGHT * 0.10;
	SrcR.x = PANEL_WIDTH * 0.05;
	SrcR.y = PANEL_HEIGHT* 0.87;

	this->copy_to_rederer_number(level, 1, SrcR, false);
}

void Player_panel_status::copy_to_rederer_ammo(int ammo) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.025;
	SrcR.h = PANEL_HEIGHT * 0.10;
	SrcR.x = PANEL_WIDTH * 0.660;
	SrcR.y = PANEL_HEIGHT - SrcR.h * 1.25;

	this->copy_to_rederer_number(ammo, 3, SrcR, false);
}

void Player_panel_status::copy_to_rederer_number(int number, int digits, SDL_Rect& SrcR, bool cero_rigth) {
	if (digits == 0) {
		return;
	}

	int id = 0;
	int order = pow(10, digits - 1);

	if (number >= order) {
		id = number / order;
		cero_rigth = true;
	} 

	if (id != 0 || cero_rigth) {
		this->number_status.copy_to_rederer(id, &SrcR); 
	}

	SrcR.x += SrcR.w + 0.01;
	this->copy_to_rederer_number(number - id * order, digits - 1,  SrcR, cero_rigth);
}

SDL_Texture* Player_panel_status::get_texture(int tex_section, int id) {
//Si el id es 2, se deberia llamar a oficial status. Hacer un switch posiblemente
	SDL_Texture* texture;
	switch(id){
		case 1:
			texture=this->guardia_status.get_texture(tex_section);
			break;
		case 2:
			texture=this->official_guard_status.get_texture(tex_section);
			break;
		case 3:
			texture=this->elite_guard_status.get_texture(tex_section);
			break;
		case 4:
			texture=this->key.get_texture(tex_section);
			break;
		case 5:
			texture=this->medical_kit.get_texture(tex_section);
			break;
		case 6:
			texture=this->treasure.get_texture(tex_section);
			break;
		case 7:
			texture=this->food.get_texture(tex_section);
			break;
		case 8:
			texture=this->automatic_gun.get_texture(tex_section);
			break;
		case 9:
			texture=this->bullets.get_texture(tex_section);
			break;
		case 10:
			texture=this->chain_cannon.get_texture(tex_section);
			break;
		default:
			texture=this->bullets.get_texture(tex_section);
			break;
	}
	/*
	if(id==1){
		return this->guardia_status.get_texture(tex_section);
	}
	if(id==2){
		return this->official_guard_status.get_texture(tex_section);
	}
	if(id==3){
		return this->elite_guard_status.get_texture(tex_section);
	}
	else{
		return this->bullets.get_texture(tex_section);
	}*/
	return texture;
	
}

