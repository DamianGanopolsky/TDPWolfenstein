#include "SoundManager.h"
#include <iostream>
#define VOLUMEN_MAXIMO 128

SoundManager::SoundManager():gunshot("../Sounds/gun_shot.wav"){
    Mix_VolumeMusic(5);
}

void SoundManager::play_sound(){
    gunshot.play(VOLUMEN_MAXIMO);
}