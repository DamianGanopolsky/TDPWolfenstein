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
    SDL_Texture* objects;
    SDL_Texture* players;
    SDL_Texture* structures;
    SDL_Texture* soldier_1;
    SDL_Texture* soldier_2;
public:
    Main_Window(SdlWindow& Window);
    void render_window();

};