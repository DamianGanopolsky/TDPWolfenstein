#include "GameObject.h"

GameObject::GameObject(const char* texturesheet, int x, int y) {
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}
GameObject::~GameObject() {}

void GameObject::update() {
    xpos++;
    srcR.h = 68;
    srcR.w = 68;
    srcR.x = 0;
    srcR.y = 0;

    destR.w = srcR.w * 2;
    destR.h = srcR.h * 2;
    destR.x = xpos;
    destR.y = ypos;
}

void GameObject::render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcR, &destR);
}