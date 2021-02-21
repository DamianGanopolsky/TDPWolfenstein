#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__


#include "SdlSound.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <unordered_map>
#include "../const.h"

class SoundManager{
private:
    std::unordered_map<int,SdlSound> SoundHash;

public:
    SoundManager();

    void play_sound(int id);
};

#endif