#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlWindow.h"
#include <map>

struct position{
    int x;
    int y;
};


class Scene{
private:
    SdlWindow& window;


public:
    Scene(SdlWindow& Window):window(Window){

    }

    void set();

    void show();

    void render();

    void draw(position& initial_pos,position& final_pos);

	~Scene();
};