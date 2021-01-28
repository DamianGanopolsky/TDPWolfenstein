#include "Player_handler.h"
#include <SDL2/SDL.h>
#include <iostream>

Player_handler::Player_handler(Player& player): 
								player(player) {
}


Player_handler::~Player_handler(){
}

bool Player_handler::handle() {
	SDL_Event event;
	quit=false;
	while(SDL_PollEvent(&event)!=0){

		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_LEFT:
						this->player.left_rotation();
						break;
					case SDLK_RIGHT:
						this->player.right_rotation();
						break;
					case SDLK_w:
						this->player.move_up();
						break;
					case SDLK_s:
						this->player.move_down();
						break;
					case SDLK_a:
						this->player.move_left();
						break;
					case SDLK_d:
						this->player.move_right();
						break; 
					case SDLK_e:
						this->player.shoot();
						break; 
					case SDLK_ESCAPE:  
						quit=true;
						break;   
				}
			case SDL_MOUSEMOTION:
				//std::cout << "En x:" << event.button.x << "En y:" << event.button.y << std::endl;
		}
	}
	return quit;
}