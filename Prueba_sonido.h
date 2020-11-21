#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Prueba_sonido{
private:
    Mix_Chunk *soundEffect;

public:
    Prueba_sonido(){
    }

    void sounds_init();

    void load_sound(const char* path_to_sound);

    void play();

	~Prueba_sonido();
};