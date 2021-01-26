#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include <vector>
#include <string>



class MapOptionsView{

private:

    SdlWindow& window;

    SDL_Texture* main_screen;

    bool active;

    std::vector<std::string> files;

public:

    MapOptionsView(SdlWindow& Window);

    bool is_active();

    void Handle_Click(int x,int y);

    void render();

};