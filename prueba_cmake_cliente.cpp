#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Prueba_sonido.h"
#include "Music.h"

int main(int argc,char* argv[]){

    std::cout << "Archivo a compilar por cmake" << std::endl;



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