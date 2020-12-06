#include "Event_Handler.h"
#include <iostream>


bool Event_Handler::handleEvents(Editor& editor){
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
            editor.HandleLeftClickPress(&event);
            break;
        case SDL_MOUSEBUTTONUP: //Evento soltar despues de clickear
            editor.HandleLeftClickRelease(&event);
            break;
        case SDL_MOUSEMOTION:
            std::cout << "En x:" << event.button.x << "En y:" << event.button.y << std::endl;
            break;
    }
    return quit;
}

Event_Handler::~Event_Handler(){

}