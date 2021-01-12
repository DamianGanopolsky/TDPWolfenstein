#include "Face_panel_status.h"
#include "../const.h"
#include <iostream>

Face_panel_status::Face_panel_status(SDL_Renderer*& renderer) :
									renderer(renderer) {
	SDL_Surface *status_img = IMG_Load("../ray_casting/panel_status/images/face1.png");
	this->faces[1] = SDL_CreateTextureFromSurface(this->renderer, status_img);
	SDL_FreeSurface(status_img);
}

Face_panel_status::Face_panel_status(Face_panel_status&& other) {
	this->faces[1] = other.faces[1];
	other.faces[1] = nullptr;	
}

Face_panel_status& Face_panel_status::operator=(Face_panel_status&& other) {
	if (this == &other) {
		return *this;
	}

	if (this->faces[1]) {
		SDL_DestroyTexture(this->faces[1]);
	}

	this->renderer = other.renderer;
	this->faces[1] = other.faces[1];
	other.faces[1] = nullptr;

	return *this;	
}

Face_panel_status::Face_panel_status() {	
}

Face_panel_status::~Face_panel_status() {
	if (this->faces[1]) {
		SDL_DestroyTexture(this->faces[1]);
	}
}

void Face_panel_status::copy_to_rederer(int health) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.1;
	SrcR.h = PANEL_HEIGHT * 0.19;
	SrcR.x = PANEL_WIDTH * 0.415;
	SrcR.y = PANEL_HEIGHT - SrcR.h;
    SDL_RenderCopy(this->renderer, this->faces[1], NULL, &SrcR);
}

