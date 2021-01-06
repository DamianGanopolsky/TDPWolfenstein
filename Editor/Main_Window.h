#include <SDL2/SDL.h>
#include "SdlClasses/SdlWindow.h"
#include <SDL2/SDL_image.h>

class Main_Window{
private:
    SdlWindow& window;
    SDL_Texture* main_window;
    SDL_Texture* save_button;
    SDL_Texture* tools;
public:
    Main_Window(SdlWindow& Window);
    void render_window();

};