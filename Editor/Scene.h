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
    SDL_Texture* player;
    SDL_Texture* treasure;
    std::map<std::pair<int,int>,SDL_Texture*> textures;


public:
    Scene(SdlWindow& Window);


    void set();

    void show();

    void render();

    void draw(position& initial_pos,position& final_pos);

	~Scene();
};