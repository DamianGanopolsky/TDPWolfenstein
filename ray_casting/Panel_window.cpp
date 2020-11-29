#include "Panel_window.h"
#include <iostream>
#include <utility>

#define PANEL_WIDTH 320
#define PANEL_HEIGHT 200
#define PANEL_TITLE "WOLFENSTEIN"
#define PANEL_DISTANCE 277
#define WALL_HEIGHT 64

Panel_window::Panel_window() : running(true) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "ERROR init video" << std::endl;
	}
	this->window = SDL_CreateWindow(PANEL_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PANEL_WIDTH, PANEL_HEIGHT, 0);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, PANEL_WIDTH, PANEL_HEIGHT);
	this->pixels = new Uint32[PANEL_WIDTH * PANEL_HEIGHT];
    memset(pixels, 255, PANEL_WIDTH * PANEL_HEIGHT * sizeof(Uint32));
}

Panel_window::~Panel_window() {
	if (this->pixels) {
		delete[] this->pixels;
	}
	if (this->texture) {
		SDL_DestroyTexture(this->texture);
	}
	if (this->renderer) {
		SDL_DestroyRenderer(this->renderer);
	}
	if (this->window) {
		SDL_DestroyWindow(this->window);
	}
	SDL_Quit();
}

bool Panel_window::is_running() {
	return this->running;
}

void Panel_window::update(std::set<Ray>&& rays) {
	if (this->pixels) {
		delete[] this->pixels;
	}
	this->pixels = new Uint32[PANEL_WIDTH * PANEL_HEIGHT];
    memset(pixels, 255, PANEL_WIDTH * PANEL_HEIGHT * sizeof(Uint32));

	for (std::set<Ray>::iterator ray = rays.begin(); ray != rays.end(); ++ray) {
		Ray ray_perp = ray->get_ray_perp();
		int proy_slice_height = ((float) WALL_HEIGHT/ (float) ray_perp.get_dist()) * (float) PANEL_DISTANCE;
		/*std::cout << "--------------------" << std::endl;
		std::cout << "number: " << ray->get_number() << std::endl;
		std::cout << "dist: " << ray->get_dist() << std::endl;
		std::cout << "point: " << ray->get_point() << std::endl;
		std::cout << "slice height: " << proy_slice_height << std::endl;*/ 
		proy_slice_height = proy_slice_height > PANEL_HEIGHT ? PANEL_HEIGHT : proy_slice_height;
		int pixel_min = (PANEL_HEIGHT - proy_slice_height) / 2;
		int pixel_max = pixel_min + proy_slice_height;
		//std::cout << pixel_min << " and " << pixel_max << std::endl; 
		for (; pixel_min < pixel_max; pixel_min++) {
    		this->pixels[pixel_min * PANEL_WIDTH + ray_perp.get_number()] = 0;
		}
	}

    SDL_UpdateTexture(this->texture, NULL, this->pixels, PANEL_WIDTH * sizeof(Uint32));
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}
