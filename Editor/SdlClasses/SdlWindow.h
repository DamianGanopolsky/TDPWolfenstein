
#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include <SDL2/SDL.h>

class SdlWindow{
private:
    //int width;
    //int height;
    SDL_Window* window;
    SDL_Renderer* renderer;


public:
    SdlWindow(int width,int height);
    
    void render();

    SDL_Renderer* getRenderer() const;

	~SdlWindow();
};
#endif