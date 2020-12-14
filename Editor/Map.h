#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include <vector>

struct position{
    int x;
    int y;
};

class Map{
private:
    std::vector <SDL_Texture*> textures;
    std::vector <SDL_Surface*> surfaces;
    position camera;
    SDL_Texture* player;
    SDL_Texture* treasure;
    SDL_Texture* bar;
    SDL_Texture* floor_tile;
    SDL_Texture* wall;
    SDL_Texture* door;
    SDL_Texture* bullets;
    SDL_Texture* medical_kit;
    SDL_Texture* automatic_gun;
    SDL_Texture* chain_cannon;
    SDL_Texture* food;
    SDL_Texture* soldier1;
    SDL_Texture* soldier2;
    SDL_Texture* soldier3;
    SdlWindow& window;

public:
    Map(SdlWindow& Window);

    void HandleMovementWASD(SDL_Event* event);

    void draw(position initial_position,position draw_position);

    void render();

	~Map();
};