#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect srcR, SDL_Rect destR) {
    SDL_RenderCopy(Game::renderer, tex, &srcR, &destR);
}