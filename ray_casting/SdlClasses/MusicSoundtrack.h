#include "SdlMusic.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <map>

class MusicSoundtrack{
private:
    Mix_Music* Main_music_soundtrack;
    //Mix_Music* Pow;

public:
    MusicSoundtrack();

    void load_editor_soundtrack();

    void play_editor();

	~MusicSoundtrack();
};