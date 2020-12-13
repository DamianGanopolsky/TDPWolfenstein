#include "SdlText.h"


SdlText::SdlText(SDL_Renderer* renderer,Uint8 r,Uint8 g,Uint8 b): renderer_(renderer){
    TTF_Init();
    color = {r, g, b};  
}

void SdlText::Load_Text(const char* path_to_ttf,const char* text\
    ,int FontSize){

    Sans = TTF_OpenFont(path_to_ttf, FontSize); 
    surfaceMessage = TTF_RenderText_Solid(Sans, text, color);

}

SDL_Surface* SdlText::getSurface(){
    return surfaceMessage;

}


SdlText::~SdlText(){
    TTF_CloseFont(Sans);
    SDL_FreeSurface(surfaceMessage);
    TTF_Quit();
}