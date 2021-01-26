#include "MapOptionsView.h"

MapOptionsView::MapOptionsView(SdlWindow& Window):window(Window),active(true){
    SDL_Surface* main_screen_surf=IMG_Load("../Editor/Editor_Assets/Mapas_Main_Screen.png");
    main_screen=SDL_CreateTextureFromSurface(window.getRenderer(),main_screen_surf);
}

bool MapOptionsView::is_active(){
    return true;
}

void MapOptionsView::Handle_Click(int x,int y){

}

void MapOptionsView::render(){
    SDL_Rect main_screen_rect={0,0,960,640};
    SDL_SetRenderDrawColor(window.getRenderer(), 128, 128, 128, 255);
    SDL_RenderCopy(window.getRenderer(),main_screen,NULL,&main_screen_rect);
}