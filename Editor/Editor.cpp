#include "Editor.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>


Editor::Editor(SdlWindow& Window):window(Window),scene(Window),is_clicked_correctly(false),is_dragging(false){
}

void Editor::HandleMotion(SDL_Event* event){
    if(is_dragging==true){
        
        final_position={event->button.x,event->button.y};
        scene.draw(initial_position,final_position);
    }
}


void Editor::HandleLeftClickPress(SDL_Event* event){
    initial_position.x=int(event->button.x);
    initial_position.y=int(event->button.y);
    if(is_clicked_correctly==true){
        is_dragging=true;
        final_position={event->button.x,event->button.y};
        scene.draw(initial_position,final_position);
    }
    else{
        is_dragging=false;
    }
}

void Editor::HandleLeftClickRelease(SDL_Event* event){
    final_position={event->button.x,event->button.y};
    is_dragging=false;
    if((initial_position.x!=int(event->button.x))||(initial_position.y!=int(event->button.y))){
        scene.draw(initial_position,final_position);
        is_clicked_correctly=false;
    }
    else{
        initial_position.x=int(event->button.x);
        initial_position.y=int(event->button.y);
        
        is_clicked_correctly=true;
        //std::cout << "asd" << std::endl;
    }
}

void Editor::HandleMovementWASD(SDL_Event* event){
    scene.HandleMovementWASD(event);
}

void Editor::render(){
    scene.render();
}

Editor::~Editor(){

}