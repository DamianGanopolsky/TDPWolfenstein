#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Game.h"
#include "TextureManager.h"

class GameObject {
    public:
        GameObject(const char* texturesheet, int x, int y);
        ~GameObject();
        void update();
        void render();

    private:
        int xpos;
        int ypos;
        SDL_Texture* objTexture;
        SDL_Rect srcR, destR;
};
#endif
