#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



struct TextBox{


    std::string box_content;

    SDL_Rect box;
    SDL_Point box_pos;

    TextBox(): box({0}),box_pos({0}){}
};