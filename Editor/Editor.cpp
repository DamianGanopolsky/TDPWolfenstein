#include "Editor.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>


Editor::Editor(SdlWindow& Window):is_clicked(false),window(Window),scene(Window){
   // scene.set();
    //scene.show();
}


void Editor::HandleLeftClickPress(SDL_Event* event){
    initial_position.x=int(event->button.x);
    initial_position.y=int(event->button.y);
    is_clicked=true;
}

void Editor::HandleLeftClickRelease(SDL_Event* event){
    std::cout << "Inicio x:" << initial_position.x<< "Inicio y:" << initial_position.y << std::endl;
    std::cout << "Fin x:" << event->button.x << "Fin y:" << event->button.y << std::endl;
    final_position={event->button.x,event->button.y};
    if((initial_position.x!=int(event->button.x))||(initial_position.y!=int(event->button.y))){
        scene.draw(initial_position,final_position);
    }
    is_clicked=false;
}

void Editor::draw(){
    scene.render();
}

Editor::~Editor(){

}