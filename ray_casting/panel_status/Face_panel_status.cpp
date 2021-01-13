#include "Face_panel_status.h"
#include "../const.h"
#include <iostream>

#define TOTAL_FACES 8
#define IMAGE_FACES_PATH "../ray_casting/panel_status/images/face"
#define MAX_HEALTH 100.0

Face_panel_status::Face_panel_status(SDL_Renderer*& renderer) : 
					Element_panel_status(renderer, IMAGE_FACES_PATH, TOTAL_FACES) {
}

Face_panel_status::Face_panel_status() :
					Element_panel_status() {
}

Face_panel_status::~Face_panel_status() {
}

Face_panel_status& Face_panel_status::operator=(Face_panel_status&& other) {
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

void Face_panel_status::copy_to_rederer(int health) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.1;
	SrcR.h = PANEL_HEIGHT * 0.19;
	SrcR.x = PANEL_WIDTH * 0.415;
	SrcR.y = PANEL_HEIGHT - SrcR.h;

	int face_number = ((MAX_HEALTH - health) / (MAX_HEALTH / (this->total_elem - 1))) + 1;
    SDL_RenderCopy(this->renderer, this->elements[face_number], NULL, &SrcR);
}
