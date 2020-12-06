#include <SDL2/SDL.h>
#include "SdlWindow.h"
#include <SDL2/SDL_image.h>

class Main_Window{
private:
    SdlWindow& window;
public:
    Main_Window(SdlWindow& Window):window(Window){

    }

    void render_window();

};