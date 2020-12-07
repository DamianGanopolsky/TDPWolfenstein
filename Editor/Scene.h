#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include <map>
#include "Map.h"
/*
struct position{
    int x;
    int y;
};*/


class Scene{
private:
    SdlWindow& window;
    SDL_Texture* player;
    SDL_Texture* treasure;
    SDL_Texture* bar;
    SDL_Texture* floor_tile;
    std::map<std::pair<int,int>,SDL_Texture*> textures;
    std::map<std::pair<int,int>,SDL_Texture*> tiles;
    int** Level;
    Map map;


public:
    Scene(SdlWindow& Window);


    void set();

    void show();

    void render();

    void HandleMovementWASD(SDL_Event* event);

    void draw(position& initial_pos,position& final_pos);

    void draw_initial_map(int** level);

	~Scene();
};