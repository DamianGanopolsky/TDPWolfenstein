#include "MapButton.h"

MapButton::MapButton(SdlWindow& Window,SDL_Rect rect,\
std::string texto):window(Window){
    file_name=texto;
    position=rect;
    SdlText texto_(window.getRenderer(),139,0,0);
    texto_.Load_Text("../OpenSans-Bold.ttf",texto,12);
    texture_of_text=SDL_CreateTextureFromSurface(window.getRenderer(), texto_.getSurface());
}

void MapButton::render(){
    SDL_RenderCopy(window.getRenderer(),texture_of_text,NULL,&position);
}

bool MapButton::is_clicked(int x,int y){
    return true;
}