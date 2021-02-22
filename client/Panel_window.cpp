#include "Panel_window.h"
#include "Elements_panel_queue.h"
#include <iostream>
#include <utility>
#include <queue>
#include <chrono>
#include "LoginView.h"
#include "LogInController.h"
#include "Yaml/YamlConfigClient.h"

Panel_window::Panel_window():  running(true) {
	this->window = SDL_CreateWindow(PANEL_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ClientConfig.screen_width, ClientConfig.screen_height, 0);
	SDL_SetWindowFullscreen(window,0);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	this->player_panel_status = Player_panel_status(this->renderer);
	//map_width=map.get_width();
	//map_height=map.get_height();
	SDL_Surface* ending_screen_surf=IMG_Load("../client/sprites/EndingScreenBase.png");
    Ending_screen_base=SDL_CreateTextureFromSurface(this->renderer,ending_screen_surf);
	SDL_Surface* waiting_screen_surf=IMG_Load("../client/sprites/waiting_screen_final.jpg");
	waiting_screen=SDL_CreateTextureFromSurface(this->renderer,waiting_screen_surf);
	SDL_FreeSurface(waiting_screen_surf);
    SDL_FreeSurface(ending_screen_surf);
	//LoginView loginview(renderer);
	//LogInController logincontroller(loginview);
	//logincontroller.run();
}

void Panel_window::load_map_dimentions(int MAP_HEIGHT,int MAP_WIDTH,int Map_Players,std::string Map_Name){
	map_height=MAP_HEIGHT;
	map_width=MAP_WIDTH;
	map_cant_players=Map_Players;
	map_name=Map_Name;
}

SDL_Renderer* Panel_window::get_renderer(){
	return renderer;
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
		
		q.push(std::move(Ray_panel(std::move(ray_perp), this->wall_textures)));

			}

	for (std::list<Game_element>::iterator element = elements.begin(); element != elements.end(); ++element) {
		if (element->is_visible()) {
			element->set_texture(this->player_panel_status.get_texture(element->get_texture_section(), element->get_type_id()));
			q.push(std::move(*element));
		}
	}

	SDL_RenderClear(this->renderer);
	int count=0;
	while(!q.empty()) {
		
		Element_panel* element = q.top();
		auto t1 = std::chrono::steady_clock::now();

		element->copy_to_rederer(*this->renderer);
		auto t2= std::chrono::steady_clock::now();
		std::chrono::duration<float, std::milli> diff;
		//std::chrono::duration<double> diff=t2-t1;
		diff = t2 - t1;
		/*if(diff.count()>0.3){
			std::cout << "El elemento que tarda es" << count << std::endl;
		}*/
		//std::cout << "Diff es" << diff.count() << std::endl;
		q.pop();
		count++;
	}
	//std::cout << "La cuenta total es" << count << std::endl;

	this->player_panel_status.copy_to_rederer(player_info);
    SDL_RenderPresent(this->renderer);
}

void Panel_window::render_player_lost_screen(){
	SDL_SetRenderDrawColor(this->renderer,105,105,105,255);
	SDL_RenderClear(this->renderer);
	SDL_Rect main_screen_rect={0,0,ClientConfig.screen_width,ClientConfig.screen_height};
    SDL_RenderCopy(this->renderer,Ending_screen_base,NULL,&main_screen_rect);
	TTF_Font* Sans = TTF_OpenFont("../client/panel_status/OpenSans-Bold.ttf", 35); 
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
	SDL_Rect main_screen_rect={0,0,ClientConfig.screen_width,ClientConfig.screen_height};
    SDL_RenderCopy(this->renderer,Ending_screen_base,NULL,&main_screen_rect);
	TTF_Font* Sans = TTF_OpenFont("../client/panel_status/OpenSans-Bold.ttf", 35); 
	if(!Sans){
		printf("TTF OPENFONT: %s \n",TTF_GetError());
	}
	float x_initial=0.0078;
	float y_initial=0.23;
	float x_treasure=0.5156;
	float x_final_score=0.359;
	float x_kills=0.6875;

	for (auto & element : final_stats) {

		SDL_Rect text_1_Rect={int(x_initial*ClientConfig.screen_width),int(y_initial*ClientConfig.screen_height),int(0.2344*ClientConfig.screen_width),int(0.1*ClientConfig.screen_height)};
		SDL_Rect text_2_Rect={int(x_treasure*ClientConfig.screen_width),int(y_initial*ClientConfig.screen_height),int(0.039*ClientConfig.screen_width),int(0.0625*ClientConfig.screen_height)};
		SDL_Rect kills_Rect={int(x_final_score*ClientConfig.screen_width),int(y_initial*ClientConfig.screen_height),int(0.039*ClientConfig.screen_width),int(0.0625*ClientConfig.screen_height)};
		SDL_Rect final_score_Rect={int(x_kills*ClientConfig.screen_width),int(y_initial*ClientConfig.screen_height),int(0.039*ClientConfig.screen_width),int(0.0625*ClientConfig.screen_height)};
		std::string treasure = std::to_string(element.score);
		std::string final_score= std::to_string(element.final_score);
		std::string kills= std::to_string(element.kills);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, element.Nickname.c_str(), {108, 0, 0});
		SDL_Surface* surfaceMessage_treas = TTF_RenderText_Solid(Sans, treasure.c_str(), {108, 0, 0});
		SDL_Surface* surfaceMessage_fscore = TTF_RenderText_Solid(Sans, final_score.c_str(), {108, 0, 0});
		SDL_Surface* surfaceMessage_kills = TTF_RenderText_Solid(Sans, kills.c_str(), {108, 0, 0});
		SDL_Texture* texture_of_text = SDL_CreateTextureFromSurface(this->renderer,surfaceMessage); 
		SDL_Texture* texture_of_treasure = SDL_CreateTextureFromSurface(this->renderer,surfaceMessage_treas);
		SDL_Texture* texture_of_fscore = SDL_CreateTextureFromSurface(this->renderer,surfaceMessage_fscore); 
		SDL_Texture* texture_of_kills = SDL_CreateTextureFromSurface(this->renderer,surfaceMessage_kills);  
		SDL_RenderCopy(this->renderer, texture_of_text, NULL, &text_1_Rect);
		SDL_RenderCopy(this->renderer, texture_of_treasure, NULL, &text_2_Rect);
		SDL_RenderCopy(this->renderer, texture_of_kills, NULL, &final_score_Rect);
		SDL_RenderCopy(this->renderer, texture_of_fscore, NULL, &kills_Rect);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(texture_of_text);
		SDL_FreeSurface(surfaceMessage_treas);
		SDL_DestroyTexture(texture_of_treasure);
		y_initial=y_initial+0.1;
	}
	TTF_CloseFont(Sans);
	SDL_RenderPresent(this->renderer);
}

void Panel_window::render_waiting_screen(){
	SDL_RenderClear(this->renderer);
	SDL_Rect main_screen_rect={0,0,ClientConfig.screen_width,ClientConfig.screen_height};
    SDL_RenderCopy(this->renderer,waiting_screen,NULL,&main_screen_rect);
	TTF_Font* Sans = TTF_OpenFont("../client/panel_status/OpenSans-Bold.ttf", 35); 
	SDL_Rect text_1_Rect={int(0.2344*ClientConfig.screen_width),int(0.5875*ClientConfig.screen_height),int(0.5469*ClientConfig.screen_width),int(0.075*ClientConfig.screen_height)};
	std::string text="Mapa elegido: "+map_name+" ("+std::to_string(map_cant_players)+" jugadores"+")";
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), {108, 0, 0});
	SDL_Texture* texture_of_text = SDL_CreateTextureFromSurface(this->renderer,surfaceMessage); 
	SDL_RenderCopy(this->renderer, texture_of_text, NULL, &text_1_Rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(texture_of_text);
	TTF_CloseFont(Sans);
	SDL_RenderPresent(this->renderer);
}

void Panel_window::load_final_stats(std::vector<Player_stats> Final_Stats){
	final_stats=Final_Stats;
}

void Panel_window::render_login_screen(){
	
}
