#include "Main_Window.h"

Main_Window::Main_Window(SdlWindow& Window):window(Window){
    SDL_Surface* tre_surface=IMG_Load("../Assets/Trophy.png");
    trophy=SDL_CreateTextureFromSurface(window.getRenderer(),tre_surface);
    SDL_Surface* player_surface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    player=SDL_CreateTextureFromSurface(window.getRenderer(),player_surface);
    SDL_Surface* bar_surface=IMG_Load("../Editor/Barra2.png");
    bar=SDL_CreateTextureFromSurface(window.getRenderer(),bar_surface);
}


void Main_Window::render_window(){
    SDL_Rect player_rect={165,608,100,80};
    SDL_Rect trophy_rect={30,630,70,70};
    SDL_Rect bar_rect={0,608,1024,92};
    SDL_RenderCopy(window.getRenderer(), bar, NULL, &bar_rect);
    SDL_RenderCopy(window.getRenderer(), trophy, NULL, &trophy_rect); 
    SDL_RenderCopy(window.getRenderer(), player, NULL, &player_rect); 
}