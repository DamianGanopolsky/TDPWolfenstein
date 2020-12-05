#include "Event_Handler.h"


bool Event_Handler::handleEvents(){
    SDL_WaitEvent(&event);
    switch (event.type){    
        case SDL_QUIT:
            quit=true;
            break;
        case SDL_KEYDOWN:

            switch(event.key.keysym.sym){
                case SDLK_a: //Tecla A
                    break;
                
                case SDLK_ESCAPE:  //Salir de la pantalla
                    quit=true;
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:  //Clickear(no necesariamente soltar)
            break;
        case SDL_MOUSEBUTTONUP: //Evento soltar despues de clickear
            break;
    }
    return quit;
}

Event_Handler::~Event_Handler(){

}