#include "MusicSoundtrack.h"
#include <iostream>
#include <unistd.h>
#include "yaml-cpp/yaml.h"


MusicSoundtrack::MusicSoundtrack(){
    Main_music_soundtrack=Mix_LoadMUS("../Music/MusicSoundtrack.mp3");
    YAML::Node config = YAML::LoadFile("../Yaml_configs/client_settings.yaml");
    int volume_music = config["Music_volume"].as<int>();
    Mix_VolumeMusic(volume_music);
}

void MusicSoundtrack::load_editor_soundtrack(){
}

void MusicSoundtrack::play_editor(){
    Mix_PlayMusic(Main_music_soundtrack,2);
}

MusicSoundtrack::~MusicSoundtrack(){
    Mix_Quit();
}