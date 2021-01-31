#include "SoundManager.h"
#include <iostream>
#define VOLUMEN_MAXIMO 128

SoundManager::SoundManager(){
    //gunshot("../Sounds/gun_shot.wav");
    //SoundHash[0]= gunsh;
    SoundHash.insert(std::make_pair(0,SdlSound("../Sounds/Knife.wav")));
    SoundHash.insert(std::make_pair(1,SdlSound("../Sounds/gun_shot.wav")));
    SoundHash.insert(std::make_pair(2,SdlSound("../Sounds/AutomaticGun.wav")));
    SoundHash.insert(std::make_pair(3,SdlSound("../Sounds/ChainCannon.wav")));
    SoundHash.insert(std::make_pair(4,SdlSound("../Sounds/opening_door.wav")));
    SoundHash.insert(std::make_pair(4,SdlSound("../Sounds/SS_Agent_death.wav")));
    Mix_VolumeMusic(5);
}

void SoundManager::play_sound(int id){
    //SoundHash[0].play(VOLUMEN_MAXIMO);
    SoundHash.at(id).play(VOLUMEN_MAXIMO);
    //gunshot.play(VOLUMEN_MAXIMO);
}