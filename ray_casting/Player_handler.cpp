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
			Command* command = new Command(START_MOVING_UP_CMD);
			//std::cout << "Opcode:" << command->get_opcode() << std::endl;
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_S])&&(moving==false)) {
			//printf("S ON.\n");
			Command* command = new Command(START_MOVING_DOWN_CMD);
			SendQueue.push(std::move(command));
			moving=true;
			
		}
		if ((state[SDL_SCANCODE_A])&&(moving==false)) {
			//printf("A ON.\n");
			Command* command = new Command(START_MOVING_LEFT_CMD);
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_D])&&(moving==false)) {
			//printf("D ON\n");
			Command* command = new Command(START_MOVING_RIGHT_CMD);
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
			Command* command = new Command(STOP_MOVING_CMD);
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
						//this->player.left_rotation();
						break;
					case SDLK_RIGHT:
						//this->player.right_rotation();
						break;
					case SDLK_w:
						//this->player.move_up();
						//std::cout << "Notifico al server que me EMPECE a  mover" << std::endl;
						break;
					case SDLK_s:
						//this->player.move_down();
						break;
					case SDLK_a:
						//this->player.move_left();
						break;
					case SDLK_d:
						//this->player.move_right();
						break; 
					case SDLK_e:{
						//Notifico al server que quiero disparar
						Command* command = new Command(USE_WEAPON_CMD);
						SendQueue.push(std::move(command));
						this->player.shoot();
						break; 
					}
					case SDLK_1:{

						Command* command = new Command(CHANGE_WEAPON_TO_KNIFE_CMD);
						SendQueue.push(std::move(command));
						
						this->player.change_weapon(0);
						//std::cout << "Notifico al server que quiero cambiar a cuchillo" << std::endl;
						break;
					}
					case SDLK_2:{
						Command* command = new Command(CHANGE_WEAPON_TO_GUN_CMD);
						SendQueue.push(std::move(command));
						this->player.change_weapon(1);
						//std::cout << "Notifico al server que quiero cambiar a pistola" << std::endl;
						break;
					}
					case SDLK_3:{
						Command* command = new Command(CHANGE_WEAPON_TO_MACHINE_GUN_CMD);
						SendQueue.push(std::move(command));
						this->player.change_weapon(2);
						//std::cout << "Notifico al server que quiero cambiar a automatic_gun" << std::endl;
						break;
					}
					case SDLK_4:{
						Command* command = new Command(CHANGE_WEAPON_TO_CHAIN_CANNON_CMD);
						SendQueue.push(std::move(command));
						this->player.change_weapon(3);
						//std::cout << "Notifico al server que quiero cambiar a chain_cannon" << std::endl;
						break;
					}
					case SDLK_5:
						//PRUEBA
						this->player.update_position_and_angle(300,300,300);
						break;
					case SDLK_6:
						this->map.update_player_pos(2,600,600,200,0);
						break;
					case SDLK_7:
						this->map.update_player_pos(2,400,400,200,0);
						break;
					case SDLK_ESCAPE:  
						//sender.stop();
						//sender.join();
						quit=true;
						break;   
				}
			case SDL_MOUSEBUTTONUP:
				if(event.button.button==SDL_BUTTON_RIGHT){
					Command* command = new Command(OPEN_DOOR_CMD);
					SendQueue.push(std::move(command));
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