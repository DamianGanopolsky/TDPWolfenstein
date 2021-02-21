#include "Ray_panel.h"
#include <utility>
#include <iostream>


Ray_panel::Ray_panel(Ray&& ray, Wall_texture& wall_textures) : ray(std::move(ray)) {
	this->dist = ray.get_dist();
	int proy_slice_height = (WALL_HEIGHT / this->ray.get_dist()) * PANEL_DISTANCE;
	int pixel_min = (PANEL_HEIGHT - proy_slice_height) / 2;
	int pixel_max = pixel_min + proy_slice_height;
	int wall_x = this->ray.get_pos_x() == 0 || this->ray.get_pos_x() == 63 ? this->ray.get_pos_y() : this->ray.get_pos_x();

	/* SOLO PARA PAREDES */
	for (int min = 0; min < PANEL_HEIGHT; min++) {
		if (min < pixel_min) {
			this->pixels[min] = FLOOR_COLOR;
		} else if (min < pixel_max) {
			int wall_y = (min - pixel_min) / (proy_slice_height / 64.0);
			int number_tex=0;
   			this->pixels[min] = wall_textures.get_pixel_tex(number_tex, wall_x, wall_y);
		} else {
			this->pixels[min] = CEILING_COLOR;
		}
	}
}

Ray_panel::Ray_panel(Ray_panel&& other) : ray(std::move(other.ray)){
	this->tex = other.tex;
	other.tex = nullptr;
	for (int i = 0; i < PANEL_HEIGHT; i++) {
		this->pixels[i] = other.pixels[i];
	}
	this->dist = other.dist;
}


Ray_panel::~Ray_panel() {
	if (this->tex) {
		SDL_DestroyTexture(this->tex);
	}
}

void Ray_panel::copy_to_rederer(SDL_Renderer& renderer) {
	this->tex = SDL_CreateTexture(&renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 1, PANEL_HEIGHT);
	SDL_Rect SrcR;
	SrcR.x = this->ray.get_number();
	SrcR.y = 0;
	SrcR.w = 1;
	SrcR.h = PANEL_HEIGHT;
	SDL_UpdateTexture(this->tex, NULL, this->pixels, sizeof(Uint32));
    SDL_RenderCopy(&renderer, this->tex, NULL, &SrcR);
}
