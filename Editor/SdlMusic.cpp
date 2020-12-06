#include "SdlMusic.h"
#include <unistd.h>

SdlMusic::SdlMusic(const char* path_to_music){
    bgm=Mix_LoadMUS(path_to_music);
    if (bgm == NULL){
        printf("Mix_LoadMP3: %s\n", Mix_GetError());
    }
}

void SdlMusic::play(){
    Mix_PlayMusic(bgm,1);
}

SdlMusic::~SdlMusic(){
    Mix_FreeMusic(bgm);
    bgm=nullptr;
}