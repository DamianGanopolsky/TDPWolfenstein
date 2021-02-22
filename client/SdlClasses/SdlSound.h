#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SdlSound{
private:
    Mix_Chunk *soundEffect;

public:
    SdlSound(const char* path_to_sound);

    void play(int volumen);
};