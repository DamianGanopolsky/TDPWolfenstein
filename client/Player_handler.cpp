#include "Player_handler.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "ClientConnector/Sender.h"
#include "../Common/protocol.h"


Player_handler::Player_handler(Player& Player,BlockingQueue<Command*>& send_queue,\
Client& Client): 
								player(Player),moving(false),rotating(false),shooting(false),\
								SendQueue(send_queue),client(Client) {
	
}


Player_handler::~Player_handler(){
}

bool Player_handler::handle() {
	SDL_Event event;
	quit=true;
	const Uint8 *state;
	while(SDL_PollEvent(&event)!=0){
		state = SDL_GetKeyboardState(NULL);
		if(state[SDL_SCANCODE_ESCAPE]){
			SendQueue.close();
			quit=false;
			break;   
		}
		if(!client.is_playing()){
			break;
		}
		if((state[SDL_SCANCODE_RETURN])&&(shooting==false)){
			auto t1 = std::chrono::steady_clock::now();
			std::chrono::duration<double> diff=t1-time_last_shoot;
			switch(player.get_weapon()){
				case 0:
				case 1:{
					Command* command=new Command(START_SHOOTING_CMD);
					SendQueue.push(std::move(command));
					shooting=true;
					break;
				}
				case 2:{
					if(diff.count()>0.6){
						Command* command=new Command(START_SHOOTING_CMD);
						SendQueue.push(std::move(command));
						shooting=true;
						time_last_shoot=std::chrono::steady_clock::now();
					}
					break;
				}
				case 3:{
					if(diff.count()>0.25){
						Command* command=new Command(START_SHOOTING_CMD);
						SendQueue.push(std::move(command));
						shooting=true;
						time_last_shoot=std::chrono::steady_clock::now();
					}
					break;
				}
			}
		}
		if ((state[SDL_SCANCODE_W])&&(moving==false)) {
			Command* command = new Command(START_MOVING_UP_CMD);
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_S])&&(moving==false)) {
			Command* command = new Command(START_MOVING_DOWN_CMD);
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_Q])&&(moving==false)) {
			Command* command = new Command(START_MOVING_LEFT_CMD);
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_E])&&(moving==false)) {
			Command* command = new Command(START_MOVING_RIGHT_CMD);
			SendQueue.push(std::move(command));
			moving=true;
		}
		if ((state[SDL_SCANCODE_D])&&(rotating==false)){
			Command* command = new Command(START_ROTATING_RIGHT);
			SendQueue.push(std::move(command));
			rotating=true;
		}
		if ((state[SDL_SCANCODE_A])&&(rotating==false)){
			Command* command = new Command(START_ROTATING_LEFT);
			SendQueue.push(std::move(command));
			rotating=true;
		}
		if (((state[SDL_SCANCODE_W]==0)&&(state[SDL_SCANCODE_Q]==0)&&\
		(state[SDL_SCANCODE_S]==0)&&(state[SDL_SCANCODE_E]==0))&&(moving)){
			Command* command = new Command(STOP_MOVING_CMD);
			SendQueue.push(std::move(command));
			moving=false;
		}
		if (((state[SDL_SCANCODE_A]==0)&&(state[SDL_SCANCODE_D]==0))&&(rotating)){
			Command* command = new Command(STOP_ROTATING);
			SendQueue.push(std::move(command));
			rotating=false;
		}
		if((state[SDL_SCANCODE_RETURN]==0)&&(shooting)){
			Command* command= new Command(STOP_SHOOTING_CMD);
			SendQueue.push(std::move(command));
			shooting=false;
		}
		switch(event.type){

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_1:{

						Command* command = new Command(CHANGE_WEAPON_TO_KNIFE_CMD);
						SendQueue.push(std::move(command));
						break;
					}
					case SDLK_2:{
						Command* command = new Command(CHANGE_WEAPON_TO_GUN_CMD);
						SendQueue.push(std::move(command));
						break;
					}
					case SDLK_3:{
						Command* command = new Command(CHANGE_WEAPON_TO_MACHINE_GUN_CMD);
						SendQueue.push(std::move(command));
						break;
					}
					case SDLK_4:{
						Command* command = new Command(CHANGE_WEAPON_TO_CHAIN_CANNON_CMD);
						SendQueue.push(std::move(command));
						break;
					}
					case SDLK_ESCAPE:  
						SendQueue.close();
						quit=false;
						break;   
				}
			case SDL_MOUSEBUTTONUP:{
				if(event.button.button==SDL_BUTTON_RIGHT){
					Command* command = new Command(OPEN_DOOR_CMD);
					SendQueue.push(std::move(command));
                }
				break;
			}
	}
	}
	return quit;
}