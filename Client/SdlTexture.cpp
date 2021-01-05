#include "SdlTexture.h"

SdlTexture::SdlTexture(SDL_Surface* surface,SdlWindow window):\
    renderer(window.getRenderer()){
    message = SDL_CreateTextureFromSurface(renderer, surface); 
}

void SdlTexture::render(int x,int y,int w,int h,SDL_Rect Message_rect,SDL_Texture* Message){
  /*  if(Message_rect==NULL){
        SDL_Rect Message_rect_={x,y,w,h};
        Message_rect = &Message_rect_;
    }
  //  SDL_Rect Message_rect;
    Message_rect->x = x;
    Message_rect->y=y;
    Message_rect->w=w;
    Message_rect->h=h; */
   // Message_rect={x,y,w,h};
   // Message_rect.x = x;  
    //Message_rect.y = y;
    //Message_rect.w = w; 
    //Message_rect.h = h;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}


SdlTexture::~SdlTexture(){
    SDL_DestroyTexture(message);
}