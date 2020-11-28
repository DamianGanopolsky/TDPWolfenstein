#include "Event_handler.h"
#include <SDL2/SDL.h>

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
    		} 
    	}
    	else if (event.type == SDL_QUIT) {
    		this->running = false;
    	}
  	}
}

bool Event_handler::is_running() {
	return this->running;
}