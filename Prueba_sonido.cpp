#include "Prueba_sonido.h"
#include <iostream>


void Prueba_sonido::sounds_init(){
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }
}

void Prueba_sonido::load_sound(const char* path_to_sound){
   soundEffect=Mix_LoadWAV(path_to_sound);
    if (soundEffect == NULL){
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
    Mix_VolumeChunk(soundEffect, MIX_MAX_VOLUME);
}

void Prueba_sonido::play(){
    Mix_PlayChannel(1, soundEffect, 3);
    while (Mix_Playing(1) != 0) {
        SDL_Delay(200); // wait 200 milliseconds
    }

}

Prueba_sonido::~Prueba_sonido(){
    Mix_FreeChunk(soundEffect);
    soundEffect=nullptr;
    Mix_Quit();
    SDL_Quit();
}