#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include "SdlClasses/SdlText.h"
#include <string>
#include "SdlClasses/SdlText.h"


class MapButton{

private:

    SdlWindow& window;
    std::string file_name;
    SDL_Rect position;
    SDL_Texture* texture_of_text;
    SDL_Texture* base;
    SDL_Rect base_position;
    

public:

    MapButton(SdlWindow& Window,SDL_Rect rect,std::string texto);

    void render();

    bool is_clicked(int x, int y);

    std::string get_file_name();


};