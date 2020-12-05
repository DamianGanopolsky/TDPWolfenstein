#include "Editor.h"
#include <iostream>


void Editor::HandleLeftClickPress(SDL_Event* event){
    initial_position.x=int(event->button.x);
    initial_position.y=int(event->button.y);
    is_clicked=true;
}

void Editor::HandleLeftClickRelease(SDL_Event* event){
    std::cout << "Inicio x:" << initial_position.x<< "Inicio y:" << initial_position.y << std::endl;
    std::cout << "Fin x:" << event->button.x << "Fin y:" << event->button.y << std::endl;
   // switch()
    is_clicked=false;
}

Editor::~Editor(){

}