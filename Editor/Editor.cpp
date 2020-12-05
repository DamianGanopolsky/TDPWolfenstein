#include "Editor.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>


void Editor::HandleLeftClickPress(SDL_Event* event){
    initial_position.x=int(event->button.x);
    initial_position.y=int(event->button.y);
    is_clicked=true;
}

void Editor::HandleLeftClickRelease(SDL_Event* event){
    std::cout << "Inicio x:" << initial_position.x<< "Inicio y:" << initial_position.y << std::endl;
    std::cout << "Fin x:" << event->button.x << "Fin y:" << event->button.y << std::endl;
    SDL_Rect Message_rect={250,250,145,80};
    SDL_Surface* tmpSurface2 = IMG_Load("../Editor/Treasure.png");
    SDL_Texture* treasureTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface2);
    SDL_RenderCopy(window.getRenderer(), treasureTex, NULL, &Message_rect); 
    is_clicked=false;
}

void Editor::draw(){

}

Editor::~Editor(){

}