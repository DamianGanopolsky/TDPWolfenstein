#include "SdlSound.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <unordered_map>

class SoundManager{
private:
    //SdlSound gunshot;
    std::unordered_map<int,SdlSound> SoundHash;

public:
    SoundManager();

    //void load_client_sounds();

    void play_sound(int id);

	//~SoundManager();
};