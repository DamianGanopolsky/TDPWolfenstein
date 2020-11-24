#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
/* QT */
//#include <QApplication>
//#include <QLabel>

#include "Prueba_sonido.h"
#include "Music.h"

int main(int argc,char* argv[]){

    std::cout << "Archivo a compilar por cmake" << std::endl;

    /* QT */
   // QApplication app(argc,argv);
    //QLabel label("Hello qt");
    //label.show();

    /* MUESTRO TEXTO CON SDL */

    bool quit = false;
    SDL_Event event;
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("SDL_ttf in SDL2",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,
    480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* Sans = TTF_OpenFont("../OpenSans-Bold.ttf", 24); 

    SDL_Color White = {255, 255, 255};  

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Wolfenstein", White);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

    SDL_Rect Message_rect; 
    Message_rect.x = 0;  
    Message_rect.y = 0;
    Message_rect.w = 500; 
    Message_rect.h = 500;

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
            quit = true;
            break;
        }

        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    TTF_CloseFont(Sans);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();

    /* PRUEBAS DE "CONCEPTO" DE MUSICA */

    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }
    Prueba_sonido sonido;
    sonido.load_sound("../Sounds/SS_Agent_death.wav");
    sonido.play();

    Music music;
    music.load_music("../Music/menu.mp3");
    music.play();

    Mix_Quit();
    SDL_Quit();

    return 0;
}