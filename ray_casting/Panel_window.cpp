#include "Panel_window.h"
#include "Elements_panel_queue.h"
#include <iostream>
#include <utility>
#include <queue>


Panel_window::Panel_window(Map_2d& MAP): map(MAP), running(true) {
	/*if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "ERROR init video" << std::endl;
	}*/
	this->window = SDL_CreateWindow(PANEL_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PANEL_WIDTH, PANEL_HEIGHT, 0);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	this->player_panel_status = Player_panel_status(this->renderer);
}

Panel_window::~Panel_window() {
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

void Panel_window::update(std::set<Ray>&& rays, std::list<Game_element>&& elements, Player_info& player_info) {
	//Cola donde estan los rayos y los elementos del juego, se renderiza primero lo que esta mas lejos.
	//Paredes, piso y techo -> rayos
	Elements_panel_queue q;
	for (std::set<Ray>::iterator ray = rays.begin(); ray != rays.end(); ++ray) {
		Ray ray_perp = ray->get_ray_perp();
		q.push(std::move(Ray_panel(std::move(ray_perp), this->wall_textures,map)));
	}
	for (std::list<Game_element>::iterator element = elements.begin(); element != elements.end(); ++element) {
		if (element->is_visible()) {
			element->set_texture(this->player_panel_status.get_texture(element->get_texture_section(), element->get_type_id()));
			q.push(std::move(*element));
		}
	}
	SDL_RenderClear(this->renderer);
	

	while(!q.empty()) {
		
		Element_panel* element = q.top();
		element->copy_to_rederer(*this->renderer);
		q.pop();
	}
	
	this->player_panel_status.copy_to_rederer(player_info);
    SDL_RenderPresent(this->renderer);
}
