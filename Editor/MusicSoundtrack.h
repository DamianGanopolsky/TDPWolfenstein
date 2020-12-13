#include "SdlClasses/SdlMusic.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <map>

class EditorSoundtrack{
private:
    Mix_Music* Suspense;
    Mix_Music* Pow;

public:
    EditorSoundtrack();

    void load_editor_soundtrack();

    void play_editor();

	~EditorSoundtrack();
};

