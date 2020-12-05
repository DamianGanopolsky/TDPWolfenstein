#include "Event_Handler.h"
#include "Editor.h"
#include <iostream>


bool Event_Handler::handleEvents(){
    SDL_WaitEvent(&event);
    Editor editor;
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
            editor.HandleLeftClickRelease(&event);
        /*    int x1=event.button.x;
            int y1=event.button.y;
            int x2,y2;
            
            while(!SDL_MOUSEBUTTONUP){

            }
            x2=event.button.x;
            y2=event.button.y;
            std::cout << "INICIO x:" << x1 << "y:" << y1 << "FINAL X:"<< x2 <<"y:" << y2 << std::endl;*/
            break;
        case SDL_MOUSEBUTTONUP: //Evento soltar despues de clickear
            editor.HandleLeftClickRelease(&event);
            break;
        case SDL_MOUSEMOTION:
            //std::cout << "Moviste el mouse" << std::endl;
           // std::cout <<"En x: "<<  event.button.x << "En y: "<< event.button.y << std::endl;
            break;
    }
    return quit;
}

Event_Handler::~Event_Handler(){

}