#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SdlText.h"
#include "SdlWindow.h"
#include "Event_Handler.h"


int main(int argc,char* argv[]){

    bool quit = false;
    Event_Handler event_handler;
   // SDL_Event event;
    SdlWindow window(640,480);
    SdlText texto(window.getRenderer(),255,255,255);
    texto.Load_Text("../OpenSans-Bold.ttf","Editor",12);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
    SDL_Rect Message_rect={225,0,100,100};
    SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect); 

    while (!quit){
        quit=event_handler.handleEvents();

     /*   SDL_WaitEvent(&event);
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
        }*/
        SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect);
        window.render();
    }
    SDL_DestroyTexture(Message);


    return 0;
}