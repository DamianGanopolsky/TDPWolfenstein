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
    SdlWindow window;

public:
    Map(SdlWindow Window);

    void update_position(position next_position);

    void draw(int object,position draw_position);

    void render();

	~Map();
};