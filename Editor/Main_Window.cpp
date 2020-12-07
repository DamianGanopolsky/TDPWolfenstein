#include "Main_Window.h"

Main_Window::Main_Window(SdlWindow& Window):window(Window){
    SDL_Surface* tmpSurface3 = IMG_Load("../Editor/Barra2.png");
    bar= SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface3);
    SDL_Surface* tmpSurface2 = IMG_Load("../Assets/Trophy.png");
    trophy = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface2);
    SDL_Surface* tmpSurface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    player = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface);
}


void Main_Window::render_window(){
    SDL_Rect Message_rect2={165,608,100,80};
    SDL_Rect Message_rect4={30,630,70,70};
    SDL_Rect Message_rect3={0,608,1024,92};
    SDL_RenderCopy(window.getRenderer(), bar, NULL, &Message_rect3);
    SDL_RenderCopy(window.getRenderer(), trophy, NULL, &Message_rect4); 
    SDL_RenderCopy(window.getRenderer(), player, NULL, &Message_rect2); 
}