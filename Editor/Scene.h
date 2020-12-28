#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include "Main_Window.h"
#include <map>
#include "Map.h"


class Scene{
private:
    SdlWindow& window;
    SDL_Texture* player;
    SDL_Texture* treasure;
    SDL_Texture* bar;
    SDL_Texture* floor_tile;
    Map map;
    Main_Window main_window;


public:
    Scene(SdlWindow& Window);

    void render();

    void expand();

    void shrink();

    void HandleMovementWASD(SDL_Event* event);

    void draw(position& initial_pos,position& final_pos);

	~Scene();
};