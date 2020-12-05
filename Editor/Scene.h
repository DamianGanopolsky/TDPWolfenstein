#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlWindow.h"


class Scene{
private:
    SdlWindow& window;


public:
    Scene(SdlWindow& Window):window(Window){

    }

    void show();

    void render();

    void draw();

	~Scene();
};