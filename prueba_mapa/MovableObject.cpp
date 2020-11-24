#include "MovableObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define HEIGHT_OBJECT 20
#define WIDTH_OBJECT 20

MovableObject::MovableObject(const char* fileName, Position &pos) {
   this->pos = pos;
   this-> tex = TextureManager::LoadTexture(fileName);

}

bool MovableObject::handle_input_arrows(SDL_Event &event) {
   if (event.type == SDL_QUIT){
      return false;
   } else if (event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym) {
         case SDLK_UP: this->pos.moveUp(); break;
         case SDLK_DOWN: this->pos.moveDown(); break;
         case SDLK_LEFT: this->pos.moveLeft(); break;
         case SDLK_RIGHT:  this->pos.moveRight(); break;    
      }
    }
   return true;

}

bool MovableObject::handle_input_asdf(SDL_Event &event) {

   if (event.type == SDL_QUIT){
      return false;
   } else if (event.type == SDL_KEYDOWN) {
      switch( event.key.keysym.sym) {
         case SDLK_w: this->pos.moveUp();std::cout <<"entra? \n"; break;
         case SDLK_s: this->pos.moveDown(); break;
         case SDLK_a: this->pos.moveLeft(); break;
         case SDLK_d: this->pos.moveRight(); break;    
      }
    }
    return true;
}

bool MovableObject::update(SDL_Event &event) {
   bool running = true;
   //running &= this->handle_input_asdf(event);
   running &= this->handle_input_arrows(event);
   
   srcR.h = 68;
   srcR.w = 68;
   srcR.x = 0;
   srcR.y = 0;

   destR.w = srcR.w * 2;
   destR.h = srcR.h * 2;
   destR.x = this->pos.getX();
   destR.y = this->pos.getY();
   return running;
}

void MovableObject::render() {
    SDL_RenderCopy(Game::renderer, this->tex, &srcR, &destR);
}
