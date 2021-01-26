#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"



class MapOptionsView{

private:

    SdlWindow& window;

    SDL_Texture* main_screen;

    bool active;

public:

    MapOptionsView(SdlWindow& Window);

    bool is_active();

    void Handle_Click(int x,int y);

    void render();

};