#include "Player_handler.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "ClientConnector/Sender.h"
#include "../Common/protocol.h"


Player_handler::Player_handler(Player& player,Map_2d& MAP,BlockingQueue<Command*>& send_queue): 
								player(player),map(MAP),moving(false),rotating(false),\
								SendQueue(send_queue) {
	//sender.start();
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
			//sender.send(1);
			//printf("W ON\n");
			//
			Command* command = new Command(1);
			//std::cout << "Opcode:" << command->get_opcode() << std::endl;
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_S])&&(moving==false)) {
			//printf("S ON.\n");
			Command* command = new Command(2);
			SendQueue.push(std::move(command));
			moving=true;
			
		}
		if ((state[SDL_SCANCODE_A])&&(moving==false)) {
			//printf("A ON.\n");
			Command* command = new Command(3);
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_D])&&(moving==false)) {
			//printf("D ON\n");
			Command* command = new Command(4);
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_RIGHT])&&(rotating==false)){
			Command* command = new Command(START_ROTATING_RIGHT);
			SendQueue.push(std::move(command));
			//printf("Rotating right on \n");
			rotating=true;
		}
		if ((state[SDL_SCANCODE_LEFT])&&(rotating==false)){
			//printf("Rotating left on \n");
			Command* command = new Command(START_ROTATING_LEFT);
			SendQueue.push(std::move(command));
			rotating=true;
		}
		if (((state[SDL_SCANCODE_W]==0)&&(state[SDL_SCANCODE_A]==0)&&\
		(state[SDL_SCANCODE_S]==0)&&(state[SDL_SCANCODE_D]==0))&&(moving)){
			//printf("STOP MOVING\n");
			Command* command = new Command(5);
			SendQueue.push(std::move(command));
			moving=false;
		}
		if (((state[SDL_SCANCODE_LEFT]==0)&&(state[SDL_SCANCODE_RIGHT]==0))&&(rotating)){
			//printf("Stop rotating \n");
			Command* command = new Command(STOP_ROTATING);
			SendQueue.push(std::move(command));
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
					case SDLK_5:
						//PRUEBA
						this->player.update_position_and_angle(300,300,300);
						break;
					case SDLK_ESCAPE:  
						//sender.stop();
						//sender.join();
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
					map.open_door(171);
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