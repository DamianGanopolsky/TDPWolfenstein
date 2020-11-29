#include "Event_handler.h"
#include <SDL2/SDL.h>
#include <iostream>

Event_handler::Event_handler(Player& player) : player(player), running(true) {
}
Event_handler::~Event_handler() {
}

void Event_handler::handle() {
	SDL_Event event;
	bool not_event = true;
  	while (this->running && not_event) {
  		SDL_WaitEvent(&event);

  		if (event.type == SDL_KEYDOWN) {
    		switch (event.key.keysym.sym) {
    			case SDLK_LEFT:
            		this->player.left_rotation();
            		not_event = false;
            		break;
        		case SDLK_RIGHT:
            		this->player.right_rotation();
            		not_event = false;
            		break;
    			case SDLK_w:
            		this->player.move_up();
            		not_event = false;
            		break;
        		case SDLK_s:
            		this->player.move_down();
            		not_event = false;
            		break;
    			case SDLK_a:
            		this->player.move_left();
            		not_event = false;
            		break;
        		case SDLK_d:
            		this->player.move_right();
            		not_event = false;
            		break;            		            		
    		}
    		std::cout << "Point: (" << this->player.get_pos_x() << ", " << this->player.get_pos_y() << ")" << std::endl;
    	}
    	else if (event.type == SDL_QUIT) {
    		this->running = false;
    	}
  	}
}

bool Event_handler::is_running() {
	return this->running;
}