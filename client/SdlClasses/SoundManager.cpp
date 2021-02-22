#include "SoundManager.h"
#include <iostream>
#define VOLUMEN_MAXIMO 128

SoundManager::SoundManager(){
    SoundHash.insert(std::make_pair(0,SdlSound("../Sounds/Knife.wav")));
    SoundHash.insert(std::make_pair(1,SdlSound("../Sounds/gun_shot.wav")));
    SoundHash.insert(std::make_pair(2,SdlSound("../Sounds/agun5bullets.wav")));
    SoundHash.insert(std::make_pair(3,SdlSound("../Sounds/ChainCannon.wav")));
    SoundHash.insert(std::make_pair(4,SdlSound("../Sounds/SS_Agent_death.wav")));
    SoundHash.insert(std::make_pair(5,SdlSound("../Sounds/EquipWeaponSound.wav")));
}

void SoundManager::play_sound(int id){
    SoundHash.at(id).play(VOLUMEN_MAXIMO);
}