#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include <vector>
#include <map>

struct position{
    int x;
    int y;
};

class Map{
private:
    std::vector <SDL_Texture*> textures;
    std::vector <SDL_Surface*> surfaces;
    std::map <int,int> player_map;
    position camera;
    SDL_Texture* Message_text;
    SdlWindow& window;
    int player_count;



public:
    Map(SdlWindow& Window);

    void HandleMovementWASD(SDL_Event* event);

    void draw(position initial_position,position draw_position);

    void render();

	~Map();
};