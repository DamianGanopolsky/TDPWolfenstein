#include "Prueba_sonido.h"
#include <iostream>

void Prueba_sonido::load_sound(const char* path_to_sound){
   soundEffect=Mix_LoadWAV(path_to_sound);
    if (soundEffect == NULL){
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
    Mix_VolumeChunk(soundEffect, MIX_MAX_VOLUME);
}

void Prueba_sonido::play(){
    Mix_PlayChannel(1, soundEffect, 1);
    while (Mix_Playing(1) != 0) {
        SDL_Delay(200); // BOrrarlo cuando el programa no termine al instante
    }

}

Prueba_sonido::~Prueba_sonido(){
    Mix_FreeChunk(soundEffect);
    soundEffect=nullptr;
}