#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



struct TextBox{


    std::string box_content;

    bool active;

    SDL_Rect box;
    SDL_Point box_pos;

    SDL_Texture* font;

    TextBox(): box({0}),box_pos({0}){}
};