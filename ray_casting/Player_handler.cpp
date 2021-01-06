#include "Player_handler.h"
#include <SDL2/SDL.h>

Player_handler::Player_handler(Player& player, bool& running): 
								player(player), running(running) {
}

Player_handler::Player_handler(Player_handler&& other) : 
								player(other.player), running(other.running){
}


Player_handler::~Player_handler(){
}

void Player_handler::handle() {
	SDL_Event event;
  	while (this->running) {
  		SDL_WaitEvent(&event);

  		if (event.type == SDL_KEYDOWN) {
    		switch (event.key.keysym.sym) {
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
    		}
    	}
    	else if (event.type == SDL_QUIT) {
    		this->running = false;
    	}
  	}
}