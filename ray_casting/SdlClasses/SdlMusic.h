#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SdlMusic{
private:
    Mix_Music* bgm;

public:
    SdlMusic(const char* path_to_music);

    void play();

	~SdlMusic();
};