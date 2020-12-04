#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SdlWindow.h"

class SdlTexture{
private:
    SDL_Texture* message;
    SDL_Renderer* renderer;
   // SDL_Rect Message_rect;

public:
    SdlTexture(SDL_Surface* surface,SdlWindow window);

    void render(int x,int y,int w,int h,SDL_Rect Message_rect,SDL_Texture* Message);

	~SdlTexture();
};