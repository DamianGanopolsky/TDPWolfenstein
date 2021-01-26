#include "MusicSoundtrack.h"
#include <iostream>
#include <unistd.h>


EditorSoundtrack::EditorSoundtrack(){
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }
    Suspense=Mix_LoadMUS("../Music/06-Suspense E1M4.mp3");
    Pow=Mix_LoadMUS("../Music/05-P.O.W. E1M3.mp3");

    Mix_VolumeMusic(2);
}

void EditorSoundtrack::load_editor_soundtrack(){
}

void EditorSoundtrack::play_editor(){
    Mix_PlayMusic(Suspense,-1);
}

EditorSoundtrack::~EditorSoundtrack(){
    Mix_Quit();
}