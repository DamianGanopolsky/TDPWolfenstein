#include "Editor.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>


Editor::Editor(SdlWindow& Window):is_clicked(false),window(Window),scene(Window){
}


void Editor::HandleLeftClickPress(SDL_Event* event){
    initial_position.x=int(event->button.x);
    initial_position.y=int(event->button.y);
}

void Editor::HandleLeftClickRelease(SDL_Event* event){
    final_position={event->button.x,event->button.y};
    if((initial_position.x!=int(event->button.x))||(initial_position.y!=int(event->button.y))){
        scene.draw(initial_position,final_position);
    }
}

void Editor::draw(){
    scene.render();
}

Editor::~Editor(){

}