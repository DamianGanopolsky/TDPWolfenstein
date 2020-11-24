#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SdlText{
private:
    SDL_Renderer* renderer_;
    SDL_Color color;
    TTF_Font* Sans;
    SDL_Surface* surfaceMessage;


public:
    SdlText(SDL_Renderer* renderer,Uint8 r,Uint8 g,Uint8 b);
    
    void Load_Text(const char* path_to_ttf,const char* text\
    ,int FontSize);

    SDL_Surface* getSurface();

	~SdlText();
};