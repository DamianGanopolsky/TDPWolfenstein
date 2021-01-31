#include "MusicSoundtrack.h"
#include <iostream>
#include <unistd.h>


MusicSoundtrack::MusicSoundtrack(){
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }

    Main_music_soundtrack=Mix_LoadMUS("../Music/FullMusicSoundtrack.mp3");
    //Pow=Mix_LoadMUS("../Music/05-P.O.W. E1M3.mp3");
    Mix_VolumeMusic(30);
}

void MusicSoundtrack::load_editor_soundtrack(){
}

void MusicSoundtrack::play_editor(){
    Mix_PlayMusic(Main_music_soundtrack,2);
    //Mix_PlayMusic(Pow,1);
}

MusicSoundtrack::~MusicSoundtrack(){
    Mix_Quit();
}