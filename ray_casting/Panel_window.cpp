#include "Panel_window.h"
#include "Elements_panel_queue.h"
#include <iostream>
#include <utility>
#include <queue>


Panel_window::Panel_window(Map_2d& MAP): map(MAP), running(true) {
	this->window = SDL_CreateWindow(PANEL_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PANEL_WIDTH, PANEL_HEIGHT, 0);
	SDL_SetWindowFullscreen(window,0);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	this->player_panel_status = Player_panel_status(this->renderer);
	map_width=map.get_width();
	map_height=map.get_height();
	SDL_Surface* ending_screen_surf=IMG_Load("../ray_casting/sprites/EndingScreenBase.png");
    Ending_screen_base=SDL_CreateTextureFromSurface(this->renderer,ending_screen_surf);
	SDL_Surface* waiting_screen_surf=IMG_Load("../ray_casting/sprites/waiting_screen_final.jpg");
	waiting_screen=SDL_CreateTextureFromSurface(this->renderer,waiting_screen_surf);
	SDL_FreeSurface(waiting_screen_surf);
    SDL_FreeSurface(ending_screen_surf);
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

void Panel_window::render_player_lost_screen(){
	SDL_SetRenderDrawColor(this->renderer,105,105,105,255);
	SDL_RenderClear(this->renderer);
	SDL_Rect main_screen_rect={0,0,PANEL_WIDTH,PANEL_HEIGHT};
    SDL_RenderCopy(this->renderer,Ending_screen_base,NULL,&main_screen_rect);
	TTF_Font* Sans = TTF_OpenFont("../ray_casting/panel_status/OpenSans-Bold.ttf", 35); 
	if(!Sans){
		printf("TTF OPENFONT: %s \n",TTF_GetError());
	}
	SDL_Rect text_1_Rect={0,100,350,30};
	const char* final_score= "Espera a que termine la partida para ver a los ganadores";
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, final_score, {108, 0, 0});
	SDL_Texture* texture_of_text = SDL_CreateTextureFromSurface(this->renderer,surfaceMessage); 
	SDL_RenderCopy(this->renderer, texture_of_text, NULL, &text_1_Rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(texture_of_text);
	TTF_CloseFont(Sans);
	SDL_RenderPresent(this->renderer);
}

void Panel_window::render_ending_screen(){
	SDL_SetRenderDrawColor(this->renderer,105,105,105,255);
	SDL_RenderClear(this->renderer);
	SDL_Rect main_screen_rect={0,0,PANEL_WIDTH,PANEL_HEIGHT};
    SDL_RenderCopy(this->renderer,Ending_screen_base,NULL,&main_screen_rect);
	TTF_Font* Sans = TTF_OpenFont("../ray_casting/panel_status/OpenSans-Bold.ttf", 35); 
	if(!Sans){
		printf("TTF OPENFONT: %s \n",TTF_GetError());
	}
	SDL_Rect text_1_Rect={0,100,350,30};
	const char* final_score= "El score final ha sido:";
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, final_score, {108, 0, 0});
	SDL_Texture* texture_of_text = SDL_CreateTextureFromSurface(this->renderer,surfaceMessage); 
	SDL_RenderCopy(this->renderer, texture_of_text, NULL, &text_1_Rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(texture_of_text);
	TTF_CloseFont(Sans);
	SDL_RenderPresent(this->renderer);
}

void Panel_window::render_waiting_screen(){
	SDL_RenderClear(this->renderer);
	SDL_Rect main_screen_rect={0,0,PANEL_WIDTH,PANEL_HEIGHT};
    SDL_RenderCopy(this->renderer,waiting_screen,NULL,&main_screen_rect);
	SDL_RenderPresent(this->renderer);
}
