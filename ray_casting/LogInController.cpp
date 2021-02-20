#include "LogInController.h"

void LogInController::run(){
    bool quit = false;

    while (!quit){
        quit=handle_events();
        //editor.render();
        //window.render();
    }


}

bool LogInController::handle_events(){

	SDL_Event event;
	bool quit=false;
	const Uint8 *state;

	//bool moving=false;
	while(SDL_PollEvent(&event)!=0){
        switch (event.type){    
            case SDL_QUIT:
                quit=true;
                break;
            case SDL_TEXTINPUT:
                break;
            case SDL_MOUSEBUTTONDOWN:  //Clickear(no necesariamente soltar)
                break;
            case SDL_MOUSEBUTTONUP: //Evento soltar despues de clickear
                break;
            case SDL_MOUSEMOTION:
                //std::cout << "En x:" << event.button.x << "En y:" << event.button.y << std::endl;
                break;
        }
    }

}
