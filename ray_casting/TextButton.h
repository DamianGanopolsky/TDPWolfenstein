#ifndef __TEXTBUTTON_H__
#define __TEXTBUTTON_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "const.h"
#include "TextBox.h"
#include "SdlClasses/SdlText.h"

class TextButton {
public:
    TextButton(SDL_Renderer*& Renderer);

    bool is_active();

    void render();

private:
	SDL_Renderer* renderer;
    TextBox textbox;
    std::vector<SdlText> caracteres;
    std::vector<SDL_Texture*> texture_of_caracter;
    SDL_Texture* button_base;

};

#endif