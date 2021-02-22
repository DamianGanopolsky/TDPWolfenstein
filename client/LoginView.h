#ifndef __LOGINVIEW_H__
#define __LOGINVIEW_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "const.h"
#include "TextButton.h"

class LoginView {
public:
    LoginView(SDL_Renderer*& Renderer);

    bool is_active();

    void handle_click(int x,int y);

    void render();

private:
    
	SDL_Renderer* renderer;
    TextButton port;
    SDL_Texture* texture_login;
};

#endif