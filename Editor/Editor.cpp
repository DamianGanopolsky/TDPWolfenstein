#include "Editor.h"
#include <iostream>


void Editor::HandleLeftClickPress(SDL_Event* event){
    std::cout << "Inicio x:" << event->button.x << "Inicio y:" << event->button.y << std::endl;
    is_clicked=true;
}

void Editor::HandleLeftClickRelease(SDL_Event* event){
    std::cout << "Inicio x:" << event->button.x << "Inicio y:" << event->button.y << std::endl;
    is_clicked=false;
}

Editor::~Editor(){

}