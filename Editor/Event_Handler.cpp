#include "Event_Handler.h"
#include <iostream>


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
                std::cout << "En x:" << event.button.x << "En y:" << event.button.y << std::endl;
                break;
        }
    }
    return quit;

}
Event_Handler::~Event_Handler(){

}