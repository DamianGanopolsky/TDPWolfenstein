#include "Event_Handler.h"
#include <iostream>


bool Event_Handler::handleEvents(Editor& editor){
    quit=false; 

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
                    case SDLK_ESCAPE:  
                        quit=true;
                        break;
                }
                break;
            case SDL_TEXTINPUT:
                editor.HandleTextInput(&event);
                break;
            case SDL_MOUSEBUTTONDOWN:  
                if(event.button.button==SDL_BUTTON_LEFT){
                    editor.HandleLeftClickPress(&event);
                }
                if(event.button.button==SDL_BUTTON_RIGHT){
                    editor.HandleRightClickPress(&event);
                }
                break;
            case SDL_MOUSEBUTTONUP: 
                if(event.button.button==SDL_BUTTON_LEFT){
                    editor.HandleLeftClickRelease(&event);
                }
                if(event.button.button==SDL_BUTTON_RIGHT){
                    editor.HandleRightClickRelease(&event);
                }
                break;
            case SDL_MOUSEMOTION:
                editor.HandleMotion(&event);
                break;
        }
    }
    return quit;
}
Event_Handler::~Event_Handler(){

}