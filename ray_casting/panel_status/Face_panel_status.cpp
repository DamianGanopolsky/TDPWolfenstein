#include "Face_panel_status.h"
#include "../const.h"
#include <string>

#define TOTAL_FACES 8
#define MAX_HEALTH 100.0
Face_panel_status::Face_panel_status(SDL_Renderer*& renderer) :
									renderer(renderer) {
	for (int i = 0; i <= TOTAL_FACES; i++) {
		std::string root("../ray_casting/panel_status/images/face");
		std::string number = std::to_string(i);
		std::string ext(".png");
		root.append(number);
		root.append(ext);
		SDL_Surface *status_img = IMG_Load(root.c_str());
		this->faces[i] = SDL_CreateTextureFromSurface(this->renderer, status_img);
		SDL_FreeSurface(status_img);
	}
}

Face_panel_status::Face_panel_status(Face_panel_status&& other) {
	for (int i = 1; i <= TOTAL_FACES; i++) {
		this->faces[i] = other.faces[i];
		other.faces[i] = nullptr;
	}
}

Face_panel_status& Face_panel_status::operator=(Face_panel_status&& other) {
	if (this == &other) {
		return *this;
	}

	for (int i = 1; i <= TOTAL_FACES; i++) {
		if (this->faces[i]) {
			SDL_DestroyTexture(this->faces[i]);
		}
	}

	this->renderer = other.renderer;

	for (int i = 1; i <= TOTAL_FACES; i++) {
		this->faces[i] = other.faces[i];
		other.faces[i] = nullptr;
	}

	return *this;	
}

Face_panel_status::Face_panel_status() {	
}

Face_panel_status::~Face_panel_status() {
	for (int i = 1; i <= TOTAL_FACES; i++) {
		if (this->faces[i]) {
			SDL_DestroyTexture(this->faces[i]);
		}
	}
}

void Face_panel_status::copy_to_rederer(int health) {
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH * 0.1;
	SrcR.h = PANEL_HEIGHT * 0.19;
	SrcR.x = PANEL_WIDTH * 0.415;
	SrcR.y = PANEL_HEIGHT - SrcR.h;

	int face_number = ((MAX_HEALTH - health) / (MAX_HEALTH / (TOTAL_FACES - 1))) + 1;

    SDL_RenderCopy(this->renderer, this->faces[face_number], NULL, &SrcR);
}

