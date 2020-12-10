#include "Event_Handler.h"
#include <iostream>


bool Event_Handler::handleEvents(Editor& editor){
    SDL_PollEvent(&event);
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
                case SDLK_ESCAPE:  //Salir de la pantalla
                    quit=true;
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:  //Clickear(no necesariamente soltar)
            std::cout << "Estoy down" << std::endl;
            editor.HandleLeftClickPress(&event);
            //is_clicking=false;
            break;
        case SDL_MOUSEBUTTONUP: //Evento soltar despues de clickear
            editor.HandleLeftClickRelease(&event);
            std::cout << "Estoy up" << std::endl;
           /* if(click==true){
                is_clicking=true;
            } */
            break;
        case SDL_MOUSEMOTION:
            //std::cout << "Estoy en motion" << std::endl;
            editor.HandleMotion(&event);
           // std::cout << "En x:" << event.button.x << "En y:" << event.button.y << std::endl;
            break;
    }
    return quit;
}

Event_Handler::~Event_Handler(){

}