#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include "SdlClasses/SdlText.h"
#include <vector>
#include <string>
#include "MapButton.h"



class MapOptionsView{

private:

    SdlWindow& window;

    SDL_Texture* main_screen;

    bool active;

    std::vector<std::string> files;

    std::vector<SDL_Texture*> textures_of_files;

    std::vector<SDL_Rect> positions;

    std::vector<MapButton> map_buttons;

public:

    MapOptionsView(SdlWindow& Window);

    bool is_active();

    void load_textures();

    std::string Handle_Click(int x,int y);

    void render();

};