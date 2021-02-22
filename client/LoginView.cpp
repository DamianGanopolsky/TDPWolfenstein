#include "LoginView.h"
#include <iostream>

LoginView::LoginView(SDL_Renderer*& Renderer):renderer(Renderer),port(Renderer){
	SDL_Surface* login_surf=IMG_Load("../client/sprites/BackgroundFinal.jpg");
    texture_login=SDL_CreateTextureFromSurface(this->renderer,login_surf);

}


bool LoginView::is_active(){
    return true;
}

void LoginView::handle_click(int x,int y){

}

void LoginView::render(){
    SDL_RenderClear(this->renderer);
	SDL_Rect main_screen_rect={0,0,PANEL_WIDTH,PANEL_HEIGHT};
    SDL_RenderCopy(this->renderer,texture_login,NULL,&main_screen_rect);
    port.render();
	SDL_RenderPresent(this->renderer);
}