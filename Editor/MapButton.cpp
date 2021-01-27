#include "MapButton.h"

MapButton::MapButton(SdlWindow& Window,SDL_Rect rect,\
std::string texto):window(Window){
    file_name=texto;
    position=rect;
    base_position=rect;
    base_position.x -= 30;
    base_position.w=800;
    SdlText texto_(window.getRenderer(),139,0,0);
    texto_.Load_Text("../OpenSans-Bold.ttf",texto,12);
    texture_of_text=SDL_CreateTextureFromSurface(window.getRenderer(), texto_.getSurface());
    SDL_Surface* base_surf=IMG_Load("../Editor/Editor_Assets/OptionBar.png");
    base=SDL_CreateTextureFromSurface(window.getRenderer(),base_surf);
}

void MapButton::render(){
    SDL_RenderCopy(window.getRenderer(),base,NULL,&base_position);
    SDL_RenderCopy(window.getRenderer(),texture_of_text,NULL,&position);
}

bool MapButton::is_clicked(int x,int y){
    return true;
}

std::string MapButton::get_file_name(){
    return file_name;
}