#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"

struct position{
    int x;
    int y;
};

class Map{
private:
    position camera;
    SDL_Texture* player;
    SDL_Texture* treasure;
    SDL_Texture* bar;
    SDL_Texture* floor_tile;
    SDL_Texture* wall;
    SDL_Texture* door;
    SDL_Texture* bullets;
    SDL_Texture* medical_kit;
    SdlWindow& window;

public:
    Map(SdlWindow& Window);

    void HandleMovementWASD(SDL_Event* event);

    void draw(position initial_position,position draw_position);

    void render();

	~Map();
};