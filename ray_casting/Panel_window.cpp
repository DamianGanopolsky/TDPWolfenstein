#include "Panel_window.h"
#include <iostream>
#include <utility>

#define PANEL_WIDTH 640
#define PANEL_HEIGHT 400
#define PANEL_TITLE "WOLFENSTEIN"
#define PANEL_DISTANCE 277
#define WALL_HEIGHT 64.0
#define FLOOR_COLOR 20
#define CEILING_COLOR 500

Panel_window::Panel_window() : running(true) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "ERROR init video" << std::endl;
	}
	this->window = SDL_CreateWindow(PANEL_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PANEL_WIDTH, PANEL_HEIGHT, 0);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, PANEL_WIDTH, PANEL_HEIGHT);
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
	this->print_floor_and_ceiling();
	for (std::set<Ray>::iterator ray = rays.begin(); ray != rays.end(); ++ray) {
		Ray ray_perp = ray->get_ray_perp();
		this->print_ray(ray_perp);
	}
	this->to_render();
}

void Panel_window::print_ray(Ray& ray) {
	int proy_slice_height = (WALL_HEIGHT / ray.get_dist()) * PANEL_DISTANCE;
	/*std::cout << "--------------------" << std::endl;
	std::cout << "number: " << ray.get_number() << std::endl;
	std::cout << "dist: " << ray.get_dist() << std::endl;
	std::cout << "point: " << ray.get_point() << std::endl;
		std::cout << "slice height: " << proy_slice_height << std::endl;*/
	proy_slice_height = proy_slice_height > PANEL_HEIGHT ? PANEL_HEIGHT : proy_slice_height;
	int pixel_min = (PANEL_HEIGHT - proy_slice_height) / 2;
	int pixel_max = pixel_min + proy_slice_height;
	int wall_x = ray.get_pos_x() == 0 || ray.get_pos_x() == 63 ? ray.get_pos_y() : ray.get_pos_x();
	for (int min = pixel_min; min < pixel_max; min++) {
		int wall_y = (min - pixel_min) / (proy_slice_height / 64.0);
		int number_tex = this->get_number_tex(ray.get_point());
   		this->pixels[min * PANEL_WIDTH + ray.get_number()] = this->wall_textures.get_pixel_tex(number_tex, wall_x, wall_y);
	}	
}

void Panel_window::print_floor_and_ceiling() {
	if (this->pixels) {
		delete[] this->pixels;
	}
	this->pixels = new Uint32[PANEL_WIDTH * PANEL_HEIGHT];
    memset(pixels, 255, PANEL_WIDTH * PANEL_HEIGHT * sizeof(Uint32));
    for (int i = 0; i < PANEL_WIDTH * PANEL_HEIGHT; i++) {
    	if (i < PANEL_WIDTH * PANEL_HEIGHT / 2) {
    		this->pixels[i] = CEILING_COLOR;
    	} else {
    		this->pixels[i] = FLOOR_COLOR;
    	}
    }
}

void Panel_window::to_render() {
    SDL_UpdateTexture(this->texture, NULL, this->pixels, PANEL_WIDTH * sizeof(Uint32));
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

int Panel_window::get_number_tex(int point) const {
	return point % 3 == 0 ? 4 : 0; 
} 	
