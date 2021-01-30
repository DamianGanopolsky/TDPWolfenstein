#include "Player_handler.h"
#include <SDL2/SDL.h>
#include <iostream>

Player_handler::Player_handler(Player& player): 
								player(player),moving(false),rotating(false) {
}


Player_handler::~Player_handler(){
}

bool Player_handler::handle() {
	SDL_Event event;
	quit=false;
	const Uint8 *state;
	//bool moving=false;
	while(SDL_PollEvent(&event)!=0){
		state = SDL_GetKeyboardState(NULL);
		if ((state[SDL_SCANCODE_W])&&(moving==false)) {
			//printf("W ON\n");
			moving=true;
		}
		if ((state[SDL_SCANCODE_S])&&(moving==false)) {
			//printf("S ON.\n");
			moving=true;
		}
		if ((state[SDL_SCANCODE_A])&&(moving==false)) {
			//printf("A ON.\n");
			moving=true;
		}
		if ((state[SDL_SCANCODE_D])&&(moving==false)) {
			//printf("D ON\n");
			moving=true;
		}
		if ((state[SDL_SCANCODE_RIGHT])&&(rotating==false)){
			//printf("Rotating right on \n");
			rotating=true;
		}
		if ((state[SDL_SCANCODE_LEFT])&&(rotating==false)){
			//printf("Rotating left on \n");
			rotating=true;
		}
		if (((state[SDL_SCANCODE_W]==0)&&(state[SDL_SCANCODE_A]==0)&&\
		(state[SDL_SCANCODE_S]==0)&&(state[SDL_SCANCODE_D]==0))&&(moving)){
			//printf("STOP MOVING\n");
			moving=false;
		}
		if (((state[SDL_SCANCODE_LEFT]==0)&&(state[SDL_SCANCODE_RIGHT]==0))&&(rotating)){
			//printf("Stop rotating \n");
			rotating=false;
		}
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
						//std::cout << "Notifico al server que me EMPECE a  mover" << std::endl;
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
						//Notifico al server que quiero disparar
						this->player.shoot();
						break; 
					case SDLK_1:
						this->player.change_weapon(0);
						//std::cout << "Notifico al server que quiero cambiar a cuchillo" << std::endl;
						break;
					case SDLK_2:
						this->player.change_weapon(1);
						//std::cout << "Notifico al server que quiero cambiar a pistola" << std::endl;
						break;
					case SDLK_3:
						this->player.change_weapon(2);
						//std::cout << "Notifico al server que quiero cambiar a automatic_gun" << std::endl;
						break;
					case SDLK_4:
						this->player.change_weapon(3);
						//std::cout << "Notifico al server que quiero cambiar a chain_cannon" << std::endl;
						break;
					case SDLK_ESCAPE:  
						quit=true;
						break;   
				}
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
					case SDLK_w:
						//std::cout << "Notifico al server que me deje de mover" << std::endl;
						break;
					/*case SDLK_a:
					case SDLK_s:
					case SDLK_d:
						std::cout << "Notifico al server que me deje de mover" << std::endl;
						break;*/
					case SDLK_RIGHT:
					case SDLK_LEFT:
						//std::cout << "Notifico al  server que deje de rotar" << std::endl;
						break;
					

				}
			case SDL_MOUSEBUTTONUP:
				if(event.button.button==SDL_BUTTON_RIGHT){
                    //std::cout << "Notifico al server que intente abrir una puerta en x:
					//<< event.button.x << "en y:" << event.button.y << std::endl;
                }
				break;

			//case SDL_MOUSEMOTION:
				//std::cout << "En x:" << event.button.x << "En y:" << event.button.y << std::endl;
		}
	}
	return quit;
}