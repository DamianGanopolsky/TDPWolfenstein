#include "SdlText.h"
#include <iostream>


SdlText::SdlText(SDL_Renderer* renderer,Uint8 r,Uint8 g,Uint8 b): renderer_(renderer){
    color = {r, g, b};  
}

void SdlText::Load_Text(const char* path_to_ttf,std::string text\
    ,int FontSize){
    char cstr[text.size() + 1];
    strcpy(cstr, text.c_str()); 
    Sans = TTF_OpenFont(path_to_ttf, FontSize); 
    surfaceMessage = TTF_RenderText_Solid(Sans, cstr, color);
}

void SdlText::close_font(){
    TTF_CloseFont(Sans);
}

SDL_Surface* SdlText::getSurface(){
    return surfaceMessage;

}
