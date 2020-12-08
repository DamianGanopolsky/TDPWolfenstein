#include <SDL2/SDL.h>
#include "SdlClasses/SdlWindow.h"
#include <SDL2/SDL_image.h>

class Main_Window{
private:
    SdlWindow& window;
    SDL_Texture* trophy;
    SDL_Texture* player;
    SDL_Texture* bar;
    SDL_Texture* medical_kit;
    SDL_Texture* bullets;
    SDL_Texture* wall;
    SDL_Texture* door;
public:
    Main_Window(SdlWindow& Window);
    void render_window();

};