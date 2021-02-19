#ifndef __LOGINVIEW_H__
#define __LOGINVIEW_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "const.h"

class LoginView {
public:
    LoginView(SDL_Renderer*& Renderer);

    bool is_active();

    void render();

private:
	SDL_Renderer* renderer;
    SDL_Texture* texture_login;
};

#endif