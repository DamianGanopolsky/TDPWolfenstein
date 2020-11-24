#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Game.h"

class TextureManager {
    public:
        static SDL_Texture* LoadTexture(const char* fileName);
        static void Draw(SDL_Texture* tex, SDL_Rect srcR, SDL_Rect destR);
};
#endif
