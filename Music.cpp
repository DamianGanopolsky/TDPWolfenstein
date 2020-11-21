#include "Music.h"
#include <unistd.h>

void Music::load_music(const char* path_to_music){
    bgm=Mix_LoadMUS(path_to_music);
    if (bgm == NULL){
        printf("Mix_LoadMP3: %s\n", Mix_GetError());
    }
}

void Music::play(){
    Mix_PlayMusic(bgm,2);
    sleep(10); //Borrarlo cuando el programa no termine al instante
}

Music::~Music(){
    Mix_FreeMusic(bgm);
    bgm=nullptr;
}