#include "LoginView.h"

LoginView::LoginView(SDL_Renderer*& Renderer):renderer(Renderer){
	SDL_Surface* login_surf=IMG_Load("../ray_casting/sprites/BackgroundFinal.png");
    texture_login=SDL_CreateTextureFromSurface(this->renderer,login_surf);
}


bool LoginView::is_active(){
    return true;
}

void LoginView::render(){
    SDL_RenderClear(this->renderer);
	SDL_Rect main_screen_rect={0,0,PANEL_WIDTH,PANEL_HEIGHT};
    SDL_RenderCopy(this->renderer,texture_login,NULL,&main_screen_rect);
	SDL_RenderPresent(this->renderer);
}