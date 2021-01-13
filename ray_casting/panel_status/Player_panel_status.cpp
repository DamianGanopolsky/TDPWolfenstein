#include "../const.h"
#include "Player_panel_status.h"
#include <SDL2/SDL_image.h>
#include <iostream>



Player_panel_status::Player_panel_status(SDL_Renderer*& renderer) :
										renderer(renderer), 
										face_status(renderer),
										weapon_status(renderer) {
	SDL_Surface *status_img = IMG_Load("../ray_casting/sprites/hud.png");
	this->status_tex = SDL_CreateTextureFromSurface(this->renderer, status_img);
	SDL_FreeSurface(status_img);
}

Player_panel_status::Player_panel_status(Player_panel_status&& other) :
										renderer(other.renderer), 
										face_status(other.renderer),
										weapon_status(other.renderer) {	
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

	SDL_Surface *pistola_img = IMG_Load("../ray_casting/sprites/pistola.png");
	SDL_Texture *pistola_tex = SDL_CreateTextureFromSurface(this->renderer, pistola_img);
	SDL_FreeSurface(pistola_img);
	SDL_Rect SrcR2;
	SrcR2.w = PANEL_WIDTH * 0.25;
	SrcR2.h = PANEL_HEIGHT * 0.25;
	SrcR2.x = (PANEL_WIDTH - SrcR2.w) / 2 ;
	SrcR2.y = SrcR.y - SrcR2.h;
    SDL_RenderCopy(this->renderer, pistola_tex, NULL, &SrcR2);
    
    if (pistola_tex) {
		SDL_DestroyTexture(pistola_tex);
	}

	this->face_status.copy_to_rederer(player_info.get_health());
	this->weapon_status.copy_to_rederer(player_info.get_weapon());
}