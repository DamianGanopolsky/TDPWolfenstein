#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Music{
private:
Mix_Music* bgm;

public:
    Music(){
    }

    void load_music(const char* path_to_music);

    void play();

	~Music();
};