#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SdlSound{
private:
    Mix_Chunk *soundEffect;

public:
    SdlSound(){
    }

    void load_sound(const char* path_to_sound);

    void play();

	~SdlSound();
};