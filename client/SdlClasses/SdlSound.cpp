#include "SdlSound.h"
#include <iostream>


SdlSound::SdlSound(const char* path_to_sound){
    soundEffect=Mix_LoadWAV(path_to_sound);
    if (soundEffect == NULL){
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
}



void SdlSound::play(int volumen){
    Mix_VolumeChunk(soundEffect, volumen);
    Mix_PlayChannel(1, soundEffect, 0);
}
