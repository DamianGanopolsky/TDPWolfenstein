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
										pistola_status(renderer, IMAGE_PISTOLAS_PATH, TOTAL_PISTOLAS),
										elite_guard_status(renderer,IMAGE_ELITE_GUARDIAS_PATH ,TOTAL_ELITE_GUARDIAS) {
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
										pistola_status(std::move(other.pistola_status)),
										elite_guard_status(std::move(other.elite_guard_status)) {	
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
	this->pistola_status = std::move(other.pistola_status);
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

	this->pistola_status.copy_to_rederer(info.get_weapon_status(), &SrcR);
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
	if(id==1){
		return this->guardia_status.get_texture(tex_section);
	}
	else{
		return this->elite_guard_status.get_texture(tex_section);
	}
	
}

