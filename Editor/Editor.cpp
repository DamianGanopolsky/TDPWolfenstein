#include "Editor.h"
#include <iostream>


void Editor::HandleLeftClickPress(SDL_Event* event){
    std::cout << "Inicio x:" << event->button.x<< "Inicio y:" << event->button.y << std::endl;
    initial_x=int(event->button.x);
    initial_y=int(event->button.y);
    std::cout << initial_x << std::endl;
    is_clicked=true;
}

void Editor::HandleLeftClickRelease(SDL_Event* event){
    std::cout << "Inicio x:" << initial_x<< "Inicio y:" << initial_y << std::endl;
    std::cout << "Fin x:" << event->button.x << "Fin y:" << event->button.y << std::endl;
    is_clicked=false;
}

Editor::~Editor(){

}