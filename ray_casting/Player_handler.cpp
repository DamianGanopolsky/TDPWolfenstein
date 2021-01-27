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
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					this->player.left_rotation();
					break;
				case SDLK_RIGHT:
					this->player.right_rotation();
					break;
				case SDLK_w:
					std::cout << "w" << std::endl;
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
		}
	}

	
	return quit;
	/*
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
                case SDLK_e:
                    this->player.shoot();
                    break;            		            		
    		}
    	}
    	else if (event.type == SDL_QUIT) {
    		this->running = false;
    	}
  	}
}
*/
}
/*
bool Event_Handler::handleEvents(Editor& editor){
    quit=false; //Agregado en los ultimos cambios


    while(SDL_PollEvent(&event)!=0){
        switch (event.type){    
            case SDL_QUIT:
                quit=true;
                break;
            case SDL_KEYDOWN:

                switch(event.key.keysym.sym){
                    case SDLK_w: //Tecla A
                    case SDLK_a:
                    case SDLK_s:
                    case SDLK_d:
                        editor.HandleMovementWASD(&event);
                        break; 
                    case SDLK_BACKSPACE:
                        editor.HandleTextInput(&event);
                        break;
                    case SDLK_ESCAPE:  //Salir de la pantalla
                        quit=true;
                        break;
                }
                break;
            case SDL_TEXTINPUT:
                editor.HandleTextInput(&event);
                //username.box_content += event.text.text;
                //texto.Load_Text("../OpenSans-Bold.ttf",username.box_content,12);
                //Message = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
                //std::cout << username.box_content << std::endl;
                break;
            case SDL_MOUSEBUTTONDOWN:  //Clickear(no necesariamente soltar)
            // editor.HandleLeftClickPress(&event);
                if(event.button.button==SDL_BUTTON_LEFT){
                    editor.HandleLeftClickPress(&event);
                }
                if(event.button.button==SDL_BUTTON_RIGHT){
                    editor.HandleRightClickPress(&event);
                }
                break;
            case SDL_MOUSEBUTTONUP: //Evento soltar despues de clickear
                if(event.button.button==SDL_BUTTON_LEFT){
                    editor.HandleLeftClickRelease(&event);
                }
                if(event.button.button==SDL_BUTTON_RIGHT){
                    editor.HandleRightClickRelease(&event);
                }
                break;
            case SDL_MOUSEMOTION:
                editor.HandleMotion(&event);
                //std::cout << "En x:" << event.button.x << "En y:" << event.button.y << std::endl;
                break;
        }
    }
    return quit;

}
*/