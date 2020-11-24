#ifndef MAP_H
#define MAP_H
#include "Game.h"
#include "TextureManager.h"

class Map {
    public:
        Map();
        ~Map();
        void LoadMap(int arr[20][25]);
        void DrawMap();

    private:
        SDL_Rect srcR, destR;
        SDL_Texture* wall;
        SDL_Texture* object;
        int map[20][25];
};
#endif