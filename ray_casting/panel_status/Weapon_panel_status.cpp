#include "Weapon_panel_status.h"
#include "../const.h"
#include <iostream>

#define TOTAL_WEAPON 4
#define IMAGE_WEAPON_PATH "../ray_casting/panel_status/images/weapon"

Weapon_panel_status::Weapon_panel_status(SDL_Renderer*& renderer) : 
					Element_panel_status(renderer, IMAGE_WEAPON_PATH, TOTAL_WEAPON) {
}

Weapon_panel_status::Weapon_panel_status() :
					Element_panel_status() {
}

Weapon_panel_status::~Weapon_panel_status() {
}

Weapon_panel_status& Weapon_panel_status::operator=(Weapon_panel_status&& other) {
	if (this == &other) {
		return *this;
	}

	for (auto it = this->elements.begin(); it != this->elements.end(); ++it) {
		if (it->second) {
			SDL_DestroyTexture(it->second);
		}
	}	

	this->renderer = other.renderer;
	this->total_elem = other.total_elem;

	for (auto it = other.elements.begin(); it != other.elements.end(); ++it) {
		this->elements[it->first] = other.elements[it->first];
		other.elements[it->first] = nullptr;
	}

	return *this;
}

void Weapon_panel_status::copy_to_rederer(int id) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.2;
	SrcR.h = PANEL_HEIGHT * 0.19;
	SrcR.x = PANEL_WIDTH * 0.795;
	SrcR.y = PANEL_HEIGHT - SrcR.h;
    SDL_RenderCopy(this->renderer, this->elements[id], NULL, &SrcR);
}