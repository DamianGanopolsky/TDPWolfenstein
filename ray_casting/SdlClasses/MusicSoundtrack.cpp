#include "MusicSoundtrack.h"
#include <iostream>
#include <unistd.h>
#include "yaml-cpp/yaml.h"


MusicSoundtrack::MusicSoundtrack(){
    /*if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }*/
    Main_music_soundtrack=Mix_LoadMUS("../Music/MusicSoundtrack.mp3");
    YAML::Node config = YAML::LoadFile("../Yaml_configs/client_settings.yaml");
    //int volume_music = config["Music_volume"].as<int>();
    Mix_VolumeMusic(128);
}

void MusicSoundtrack::load_editor_soundtrack(){
}

void MusicSoundtrack::play_editor(){
    Mix_PlayMusic(Main_music_soundtrack,2);
}

MusicSoundtrack::~MusicSoundtrack(){
    Mix_Quit();
}