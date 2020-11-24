#ifndef MOVABLE_OBJECT_H_
#define MOVABLE_OBJECT_H_

#include "position.h"
#include "TextureManager.h"

class MovableObject {
 private:
    SDL_Event event;
    SDL_Texture* tex;
    Position pos;
    SDL_Rect srcR, destR;
    //int xVel;
    //int yVel;
    bool handle_input_arrows(SDL_Event &event);
    bool handle_input_asdf(SDL_Event &event);

 public:
    MovableObject(const char* fileName, Position &pos);
    bool update(SDL_Event &event);
    void render();
};

#endif   // MOVABLE_OBJECT_H_
