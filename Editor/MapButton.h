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
    

public:

    MapButton(SdlWindow& Window,SDL_Rect rect,std::string texto);

    void render();

    bool is_clicked(int x, int y);


};