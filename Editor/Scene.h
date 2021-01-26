#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include "Main_Window.h"
#include <map>
#include "Map.h"
#include "InputTextView.h"
//#include "TextBox.h"


class Scene{
private:
    SdlWindow& window;
    SDL_Texture* player;
    SDL_Texture* treasure;
    SDL_Texture* bar;
    SDL_Texture* floor_tile;
    Map map;
    Main_Window main_window;
    InputTextView InputView;


public:
    Scene(SdlWindow& Window,std::string YamlPath);

    void render();

    void click(position final_pos);

    //void HandleMovementWASD(SDL_Event* event);

    void HandleKeyPressed(SDL_Event* event);

    void draw(position& initial_pos,position& final_pos);

    void SaveMap(std::string PathToFile);

	~Scene();
};