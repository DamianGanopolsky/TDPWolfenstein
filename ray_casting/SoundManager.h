#include "SdlClasses/SdlSound.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <map>

class SoundManager{
private:
    SdlSound gunshot;

public:
    SoundManager();

    //void load_client_sounds();

    void play_sound();

	//~SoundManager();
};