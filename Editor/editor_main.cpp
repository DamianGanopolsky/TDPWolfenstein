#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SdlText.h"
#include "SdlWindow.h"
#include "Event_Handler.h"


int main(int argc,char* argv[]){

    bool quit = false;
    Event_Handler event_handler;
    
    SdlWindow window(1024,760);
    SdlText texto(window.getRenderer(),255,255,255);
    texto.Load_Text("../OpenSans-Bold.ttf","Editor",12);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
    SDL_Rect Message_rect={80,605,145,80};
    SDL_Rect Message_rect4={30,605,80,80};
    SDL_Rect Message_rect3={0,600,1000,100};
    SDL_Surface* tmpSurface3 = IMG_Load("../Editor/Barra.png");
    SDL_Texture* barTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface3);
    SDL_Surface* tmpSurface2 = IMG_Load("../Editor/Treasure.png");
    SDL_Texture* treasureTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface2);
    SDL_Surface* tmpSurface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    SDL_Texture* playerTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface);
    SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect); 
    
    SDL_RenderCopy(window.getRenderer(), barTex, NULL, &Message_rect3);
    SDL_RenderCopy(window.getRenderer(), treasureTex, NULL, &Message_rect4); 
    SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect); 
    Editor editor(window);
     

    while (!quit){
        quit=event_handler.handleEvents(editor);
        //SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect);
         
        //SDL_RenderCopy(window.getRenderer(), barTex, NULL, &Message_rect3); 
        //SDL_RenderCopy(window.getRenderer(), treasureTex, NULL, &Message_rect4); 
        //SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect);
        
        window.render();
    }
    SDL_DestroyTexture(Message);


    return 0;
}