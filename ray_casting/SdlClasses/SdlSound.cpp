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
/*
SdlSound::SdlSound(SdlSound&& other){
    soundEffect=other.soundEffect;
    other.soundEffect=NULL;
}

SdlSound& SdlSound::operator=(SdlSound&& other){
    if(this == &other){
        return *this;
    }
    this->soundEffect=other.soundEffect;
    other.soundEffect=NULL;
    return *this;
}*/

SdlSound::~SdlSound(){
    //if(soundEffect){
     //   Mix_FreeChunk(soundEffect);
    //}
    //Mix_FreeChunk(soundEffect);
    //soundEffect=nullptr;
}