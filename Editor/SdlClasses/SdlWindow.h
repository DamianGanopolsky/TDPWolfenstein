
#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include <SDL2/SDL.h>

class SdlWindow{
private:
    float Width;
    float Height;
    SDL_Window* window;
    SDL_Renderer* renderer;


public:
    SdlWindow(float width,float height);
    
    void render();

    float getHeight() const;

    float getWidth() const;

    void set_full_screen();

    SDL_Renderer* getRenderer() const;

	~SdlWindow();
};
#endif